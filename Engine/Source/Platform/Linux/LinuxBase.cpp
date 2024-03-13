#include <Platform/Linux/LinuxBase.h>

#include <Engine/EngineLoop.h>

#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <sys/time.h>
#include <time.h>
#include <pthread.h>
#include <errno.h>

// X11 headers
#include <X11/extensions/Xrender.h> 
#include <xcb/xproto.h> 
#include <X11/XKBlib.h> 
#include <X11/Xlib-xcb.h> 
#include <X11/Xlib.h> 
#include <X11/Xresource.h> 
#include <X11/extensions/Xrandr.h> 
#include <X11/keysym.h> 
#include <xcb/xcb.h> 

namespace Neowise::Platform::Linux {

    struct _WindowData {
        Display             *pDisplay = nullptr;
        xcb_connection_t    *pHandleConnection = nullptr;
        xcb_window_t         handle = 0;
        xcb_screen_t        *pScreen = nullptr;
        xcb_atom_t           wmProtocols = 0;
        xcb_atom_t           wmDeleteWin = 0;
        FVec2                screenSize = {};
    };

    struct _WindowStorage {
        _WindowData data[4] = {};
        uint count = {};
    } static GWindows = {};

    inline auto& allocWindowData(_WindowID& id) {
        id = GWindows.count++;
        return GWindows.data[id];
    }

    inline auto& getWindowData(_WindowID id) {
        return GWindows.data[id];
    }

    void *_AlignedAlloc(uint size, uint alignment) {
        return malloc(size);
    }

    void _AlignedFree(void *p) {
        free(p);
    }

    void *_MemoryCopy(void *dst, const void *src, uint size) {
        return memcpy(dst, src, size);
    }

    void *_MemorySet(void *dst, int32 value, uint size) {
        return memset(dst, value, size);
    }
    uint _MemoryCount(const char *s) {
        return strlen(s);
    }

    uint _MemoryCount(const wchar_t *ws) {
        return strlen((const char*)ws) / 2;
    }

    bool _MemoryCompare(const void *p1, const void *p2, uint size) {
        return memcmp(p1, p2, size) == 0;
    }

    void _ConsoleWrite(const char *text)
    {
        fprintf(stdout, "%s", text);
    }

    real _GetAbsoluteTime() {
        struct timespec now;
        clock_gettime(CLOCK_MONOTONIC_RAW, &now);
        const auto tmp = now.tv_sec + now.tv_nsec * 0.000000001;
        return tmp;
    }

    uint _ThreadCreate(uint &threadID, void *(*startFn)(void *), void *params) {
        const auto ret = pthread_create((pthread_t *)&threadID, nullptr, startFn, params);
        if (ret == 0) return 0;

        switch (ret) {
            case EAGAIN: return E_THREAD_ERROR_AGAIN;
            case EINVAL: return E_THREAD_ERROR_INVALID_VALUE;
        }

        return E_THREAD_ERROR_UNKNOWN;
    }

    uint _ThreadDetach(uint threadID) {
        const auto ret = pthread_detach((pthread_t)threadID);
        if (ret == 0) return 0;

        switch (ret) {
            case ESRCH:  return E_THREAD_ERROR_SEARCH;
            case EINVAL: return E_THREAD_ERROR_INVALID_VALUE;
        }

        return E_THREAD_ERROR_UNKNOWN;
    }

    uint _ThreadCancel(uint threadID) {
        const auto ret = pthread_cancel((pthread_t)threadID);
        if (ret == 0) return 0;

        switch (ret) {
            case ESRCH:  return E_THREAD_ERROR_SEARCH;
        }

        return E_THREAD_ERROR_UNKNOWN;
    }

    uint _InterlockValue(volatile uint *pValue) {
        return __sync_lock_test_and_set(pValue, 1);
    }

    void _BreakProcess() {
        __builtin_trap();
    }

    uint _WindowCreate(_WindowID &id, const CStringView &name, const Point2i &pos, const FVec2 &size) {
        if (!(size.x && size.y)) {
            return E_WINDOW_ERROR_INVALID_ARGUMENTS;
        }

        _WindowData& win = allocWindowData(id);
        win.pDisplay = XOpenDisplay(nullptr);
        XAutoRepeatOff(win.pDisplay);
        win.pHandleConnection = XGetXCBConnection(win.pDisplay);
        if (xcb_connection_has_error(win.pHandleConnection)) {
            GDiag << "Failed to connect to X server via XCB!\n";
            return E_WINDOW_ERROR_X_MISSING;
        }

        const struct xcb_setup_t *setup = xcb_get_setup(win.pHandleConnection);

        win.pScreen = xcb_setup_roots_iterator(setup).data;

        win.handle = xcb_generate_id(win.pHandleConnection);

        // Register event types.
        // XCB_CW_BACK_PIXEL = filling then window bg with a single colour
        // XCB_CW_EVENT_MASK is required.
        uint32 event_mask =   XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;

        // Listen for keyboard and mouse buttons
        uint32 event_values = XCB_EVENT_MASK_BUTTON_PRESS | XCB_EVENT_MASK_BUTTON_RELEASE |
                              XCB_EVENT_MASK_KEY_PRESS | XCB_EVENT_MASK_KEY_RELEASE |
                              XCB_EVENT_MASK_EXPOSURE | XCB_EVENT_MASK_POINTER_MOTION |
                              XCB_EVENT_MASK_STRUCTURE_NOTIFY;

        // Values to be sent over XCB (bg colour, events)
        uint32 value_list[2] = { win.pScreen->black_pixel, event_values };

        xcb_create_window(
            win.pHandleConnection,
            XCB_COPY_FROM_PARENT,
            win.handle,
            win.pScreen->root,
            pos.x,
            pos.y,
            uint16(size.x),
            uint16(size.y),
            0,
            XCB_WINDOW_CLASS_INPUT_OUTPUT,
            win.pScreen->root_visual,
            event_mask,
            value_list
        );

        xcb_change_property(
            win.pHandleConnection,
            XCB_PROP_MODE_REPLACE,
            win.handle,
            XCB_ATOM_WM_NAME,
            XCB_ATOM_STRING,
            8,
            name.size(),
            name.cstr()
        );

        static const CStringView wmDeleteWindowName("WM_DELETE_WINDOW");
        static const CStringView wmProtocolsName("WM_PROTOCOLS");

        // Tell the server to notify when the window manager
        // attempts to destroy the window.
        xcb_intern_atom_cookie_t wm_delete_cookie = xcb_intern_atom(
            win.pHandleConnection,
            0,
            (uint16)wmDeleteWindowName.size(),
            wmDeleteWindowName.cstr());

        xcb_intern_atom_cookie_t wm_protocols_cookie = xcb_intern_atom(
            win.pHandleConnection,
            0,
            (uint16)wmProtocolsName.size(),
            wmProtocolsName.cstr());
        xcb_intern_atom_reply_t* wm_delete_reply = xcb_intern_atom_reply(
            win.pHandleConnection,
            wm_delete_cookie,
            NULL);
        xcb_intern_atom_reply_t* wm_protocols_reply = xcb_intern_atom_reply(
            win.pHandleConnection,
            wm_protocols_cookie,
            NULL);
        win.wmDeleteWin = wm_delete_reply->atom;
        win.wmProtocols = wm_protocols_reply->atom;

        xcb_change_property(
            win.pHandleConnection,
            XCB_PROP_MODE_REPLACE,
            win.handle,
            wm_protocols_reply->atom,
            4,
            32,
            1,
            &wm_delete_reply->atom);

        // Map the window to the screen
        xcb_map_window(win.pHandleConnection, win.handle);

        // Flush the stream
        int32 stream_result = xcb_flush(win.pHandleConnection);
        if (stream_result <= 0) {
            GDiag << "An error occurred when flusing the stream: " << stream_result << "\n";
            return E_WINDOW_ERROR_BAD_FLUSH;
        }

        return 0;
    }

    uint _WindowDestroy(_WindowID &id) {
        if (id != -1) {
            _WindowData& win = getWindowData(id);
            XAutoRepeatOn(win.pDisplay);
            xcb_destroy_window(win.pHandleConnection, win.handle);
            GWindows.count--;
            id = -1;
        }
        return 0;
    }

    bool _WindowPumpMessages(const _WindowID &id, void *params) {
        if (id == -1) return false;

        _WindowData& win = getWindowData(id);
        _WindowInputInfo* input = (_WindowInputInfo *)params;

        xcb_generic_event_t *event = nullptr;
        xcb_client_message_event_t *cm = nullptr;

        while ((event = xcb_poll_for_event(win.pHandleConnection))) {
            switch (event->response_type & ~0x80) {
                default: break;

                case XCB_CLIENT_MESSAGE: {
                    cm = (xcb_client_message_event_t*)event;

                    // Window close
                    if (cm->data.data32[0] == win.wmDeleteWin) {
                        GEngineLoop->requestExit(0);
                    }
                } break;

                case XCB_KEY_PRESS:
                case XCB_KEY_RELEASE: {
                    // Key press event - xcb_key_press_event_t and xcb_key_release_event_t are the same
                    xcb_key_press_event_t* kb_event = (xcb_key_press_event_t*)event;
                    bool pressed = event->response_type == XCB_KEY_PRESS;
                    xcb_keycode_t code = kb_event->detail;
                    KeySym key_sym = XkbKeycodeToKeysym(
                        win.pDisplay,
                        (KeyCode)code,  // event.xkey.keycode,
                        0,
                        0 /*code & ShiftMask ? 1 : 0*/);

                    EKey key;
                    EKeyMod mod;
                    _TranslateKey(key_sym, key, mod);
                    input->pKeysState[int32(key)] = pressed ? E_TOGGLE_STATE_PRESSED : E_TOGGLE_STATE_RELEASED;
                    input->pKeyMods[int32(key)] = mod;
                } break;
            }

            free(event);
        }

        return true;
    }

    void _WindowSetTitle(const _WindowID &id, const CStringView &name) {
        const _WindowData& win = getWindowData(id);

        xcb_change_property(
            win.pHandleConnection,
            XCB_PROP_MODE_REPLACE,
            win.handle,
            XCB_ATOM_WM_NAME,
            XCB_ATOM_STRING,
            8,
            name.size(),
            name.cstr()
        );
    }

    void _WindowSetPlacement(const _WindowID &id, const Point2i &pos, const FVec2 &size) {
        const _WindowData& win = getWindowData(id);

        const uint32 values[] = {
            uint32(pos.x),
            uint32(pos.y),
            uint32(size.x),
            uint32(size.y)
        };

        xcb_configure_window(win.pHandleConnection, win.handle, 
        0 
        | XCB_CONFIG_WINDOW_X 
        | XCB_CONFIG_WINDOW_Y 
        | XCB_CONFIG_WINDOW_WIDTH 
        | XCB_CONFIG_WINDOW_HEIGHT, 
        values);
    }

#define _check_key(_in_, _key_, _mod_) case _in_: { key = _key_; mod = _mod_; } return

    void _TranslateKey(const uint in, EKey &key, EKeyMod &mod) {
        switch (in) {
            _check_key(XK_BackSpace,    E_KEY_BACKSPACE,    E_KEY_MOD_ANY);
            _check_key(XK_Return,       E_KEY_ENTER,        E_KEY_MOD_ANY);
            _check_key(XK_Tab,          E_KEY_TAB,          E_KEY_MOD_ANY);
            _check_key(XK_Caps_Lock,    E_KEY_CAPSLOCK,     E_KEY_MOD_ANY);
            _check_key(XK_Escape,       E_KEY_ESCAPE,       E_KEY_MOD_ANY);
            _check_key(XK_space,        E_KEY_SPACE,        E_KEY_MOD_ANY);
            _check_key(XK_Left,         E_KEY_ARROW_L,      E_KEY_MOD_ANY);
            _check_key(XK_Up,           E_KEY_ARROW_U,      E_KEY_MOD_ANY);
            _check_key(XK_Right,        E_KEY_ARROW_R,      E_KEY_MOD_ANY);
            _check_key(XK_Down,         E_KEY_ARROW_D,      E_KEY_MOD_ANY);
            _check_key(XK_Delete,       E_KEY_DEL,          E_KEY_MOD_ANY);
            _check_key(XK_Meta_L,       E_KEY_SUPER,        E_KEY_MOD_LEFT);
            _check_key(XK_Meta_R,       E_KEY_SUPER,        E_KEY_MOD_RIGHT);
            _check_key(XK_KP_0,         E_KEY_0,            E_KEY_MOD_ANY);
            _check_key(XK_0,            E_KEY_0,            E_KEY_MOD_ANY);
            _check_key(XK_KP_1,         E_KEY_1,            E_KEY_MOD_ANY);
            _check_key(XK_1,            E_KEY_1,            E_KEY_MOD_ANY);
            _check_key(XK_KP_2,         E_KEY_2,            E_KEY_MOD_ANY);
            _check_key(XK_2,            E_KEY_2,            E_KEY_MOD_ANY);
            _check_key(XK_KP_3,         E_KEY_3,            E_KEY_MOD_ANY);
            _check_key(XK_3,            E_KEY_3,            E_KEY_MOD_ANY);
            _check_key(XK_KP_4,         E_KEY_4,            E_KEY_MOD_ANY);
            _check_key(XK_4,            E_KEY_4,            E_KEY_MOD_ANY);
            _check_key(XK_KP_5,         E_KEY_5,            E_KEY_MOD_ANY);
            _check_key(XK_5,            E_KEY_5,            E_KEY_MOD_ANY);
            _check_key(XK_KP_6,         E_KEY_6,            E_KEY_MOD_ANY);
            _check_key(XK_6,            E_KEY_6,            E_KEY_MOD_ANY);
            _check_key(XK_KP_7,         E_KEY_7,            E_KEY_MOD_ANY);
            _check_key(XK_7,            E_KEY_7,            E_KEY_MOD_ANY);
            _check_key(XK_KP_8,         E_KEY_8,            E_KEY_MOD_ANY);
            _check_key(XK_8,            E_KEY_8,            E_KEY_MOD_ANY);
            _check_key(XK_KP_9,         E_KEY_9,            E_KEY_MOD_ANY);
            _check_key(XK_9,            E_KEY_9,            E_KEY_MOD_ANY);
            //_check_key(XK_multiply,     E_KEY_,            E_KEY_MOD_ANY);
            _check_key(XK_minus,        E_KEY_MINUS,        E_KEY_MOD_ANY);
            _check_key(XK_equal,        E_KEY_EQUALS,       E_KEY_MOD_ANY);
            _check_key(XK_F1,           E_KEY_FUNC1,        E_KEY_MOD_ANY);
            _check_key(XK_F2,           E_KEY_FUNC2,        E_KEY_MOD_ANY);
            _check_key(XK_F3,           E_KEY_FUNC3,        E_KEY_MOD_ANY);
            _check_key(XK_F4,           E_KEY_FUNC4,        E_KEY_MOD_ANY);
            _check_key(XK_F5,           E_KEY_FUNC5,        E_KEY_MOD_ANY);
            _check_key(XK_F6,           E_KEY_FUNC6,        E_KEY_MOD_ANY);
            _check_key(XK_F7,           E_KEY_FUNC7,        E_KEY_MOD_ANY);
            _check_key(XK_F8,           E_KEY_FUNC8,        E_KEY_MOD_ANY);
            _check_key(XK_F9,           E_KEY_FUNC9,        E_KEY_MOD_ANY);
            _check_key(XK_F10,          E_KEY_FUNC10,       E_KEY_MOD_ANY);
            _check_key(XK_A,            E_KEY_A,            E_KEY_MOD_ANY);
            _check_key(XK_a,            E_KEY_A,            E_KEY_MOD_ANY);
            _check_key(XK_B,            E_KEY_B,            E_KEY_MOD_ANY);
            _check_key(XK_b,            E_KEY_B,            E_KEY_MOD_ANY);
            _check_key(XK_C,            E_KEY_C,            E_KEY_MOD_ANY);
            _check_key(XK_c,            E_KEY_C,            E_KEY_MOD_ANY);
            _check_key(XK_D,            E_KEY_D,            E_KEY_MOD_ANY);
            _check_key(XK_d,            E_KEY_D,            E_KEY_MOD_ANY);
            _check_key(XK_E,            E_KEY_E,            E_KEY_MOD_ANY);
            _check_key(XK_e,            E_KEY_E,            E_KEY_MOD_ANY);
            _check_key(XK_F,            E_KEY_F,            E_KEY_MOD_ANY);
            _check_key(XK_f,            E_KEY_F,            E_KEY_MOD_ANY);
            _check_key(XK_G,            E_KEY_G,            E_KEY_MOD_ANY);
            _check_key(XK_g,            E_KEY_G,            E_KEY_MOD_ANY);
            _check_key(XK_H,            E_KEY_H,            E_KEY_MOD_ANY);
            _check_key(XK_h,            E_KEY_H,            E_KEY_MOD_ANY);
            _check_key(XK_I,            E_KEY_I,            E_KEY_MOD_ANY);
            _check_key(XK_i,            E_KEY_I,            E_KEY_MOD_ANY);
            _check_key(XK_J,            E_KEY_J,            E_KEY_MOD_ANY);
            _check_key(XK_j,            E_KEY_J,            E_KEY_MOD_ANY);
            _check_key(XK_K,            E_KEY_K,            E_KEY_MOD_ANY);
            _check_key(XK_k,            E_KEY_K,            E_KEY_MOD_ANY);
            _check_key(XK_L,            E_KEY_L,            E_KEY_MOD_ANY);
            _check_key(XK_l,            E_KEY_L,            E_KEY_MOD_ANY);
            _check_key(XK_M,            E_KEY_M,            E_KEY_MOD_ANY);
            _check_key(XK_m,            E_KEY_M,            E_KEY_MOD_ANY);
            _check_key(XK_N,            E_KEY_N,            E_KEY_MOD_ANY);
            _check_key(XK_n,            E_KEY_N,            E_KEY_MOD_ANY);
            _check_key(XK_O,            E_KEY_O,            E_KEY_MOD_ANY);
            _check_key(XK_o,            E_KEY_O,            E_KEY_MOD_ANY);
            _check_key(XK_P,            E_KEY_P,            E_KEY_MOD_ANY);
            _check_key(XK_p,            E_KEY_P,            E_KEY_MOD_ANY);
            _check_key(XK_Q,            E_KEY_Q,            E_KEY_MOD_ANY);
            _check_key(XK_q,            E_KEY_Q,            E_KEY_MOD_ANY);
            _check_key(XK_R,            E_KEY_R,            E_KEY_MOD_ANY);
            _check_key(XK_r,            E_KEY_R,            E_KEY_MOD_ANY);
            _check_key(XK_S,            E_KEY_S,            E_KEY_MOD_ANY);
            _check_key(XK_s,            E_KEY_S,            E_KEY_MOD_ANY);
            _check_key(XK_T,            E_KEY_T,            E_KEY_MOD_ANY);
            _check_key(XK_t,            E_KEY_T,            E_KEY_MOD_ANY);
            _check_key(XK_U,            E_KEY_U,            E_KEY_MOD_ANY);
            _check_key(XK_u,            E_KEY_U,            E_KEY_MOD_ANY);
            _check_key(XK_V,            E_KEY_V,            E_KEY_MOD_ANY);
            _check_key(XK_v,            E_KEY_V,            E_KEY_MOD_ANY);
            _check_key(XK_W,            E_KEY_W,            E_KEY_MOD_ANY);
            _check_key(XK_w,            E_KEY_W,            E_KEY_MOD_ANY);
            _check_key(XK_X,            E_KEY_X,            E_KEY_MOD_ANY);
            _check_key(XK_x,            E_KEY_X,            E_KEY_MOD_ANY);
            _check_key(XK_Y,            E_KEY_Y,            E_KEY_MOD_ANY);
            _check_key(XK_y,            E_KEY_Y,            E_KEY_MOD_ANY);
            _check_key(XK_Z,            E_KEY_Z,            E_KEY_MOD_ANY);
            _check_key(XK_z,            E_KEY_Z,            E_KEY_MOD_ANY);
            _check_key(XK_Shift_L,      E_KEY_SHIFT,        E_KEY_MOD_LEFT);
            _check_key(XK_Shift_R,      E_KEY_SHIFT,        E_KEY_MOD_RIGHT);
            _check_key(XK_Control_L,    E_KEY_CONTROL,      E_KEY_MOD_LEFT);
            _check_key(XK_Control_R,    E_KEY_CONTROL,      E_KEY_MOD_RIGHT);
            _check_key(XK_Alt_L,        E_KEY_ALT,          E_KEY_MOD_LEFT);
            _check_key(XK_Alt_R,        E_KEY_ALT,          E_KEY_MOD_RIGHT);
            _check_key(XK_semicolon,    E_KEY_SEMICOLON,    E_KEY_MOD_ANY);
            _check_key(XK_comma,        E_KEY_COMMA,        E_KEY_MOD_ANY);
            default: break;
        }
    }

}
