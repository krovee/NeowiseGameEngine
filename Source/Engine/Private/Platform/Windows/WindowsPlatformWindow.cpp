#include <Platform/Windows/WindowsPlatformWindow.h>


#include <Engine/EngineLoop.h>
#include <Engine/EngineEvents.h>
#include <Engine/Events/Bus.h>

#include <Base/BuildVersion.h>

namespace Neowise::Platform {
    namespace {
        wchar_t* itoa(TUint64 value, wchar_t* result, int base) {
            if (base < 2 || base > 36) { *result = '\0'; return result; }

            wchar_t* ptr = result, * ptr1 = result, tmp_char;
            TUint64 tmp_value;

            do {
                tmp_value = value;
                value /= base;
                *ptr++ = L"zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"[35 + (tmp_value - value * base)];
            } while (value);

            // Apply negative sign
            if (tmp_value < 0) *ptr++ = '-';
            *ptr-- = '\0';

            // Reverse the string
            while (ptr1 < ptr) {
                tmp_char = *ptr;
                *ptr-- = *ptr1;
                *ptr1++ = tmp_char;
            }
            return result;
        }

        static FVec2 sGetScreenSize() {
            static FVec2 screenSize{
                TReal(Windows::getPrimaryMonitorWidth()),
                TReal(Windows::getPrimaryMonitorHeight())
            };
            return screenSize;
        }
    } // 8

    Windows::CBaseWindow::CBaseWindow(defaultCreateTag) 
    : Neowise::CBaseWindow({0, 0}, sGetScreenSize() / 2, false, true, false, true)
    {
        CStringBuilder s(_title);
        s << "Neowise Engine (build." << TUint(buildVersion) << ")";
        _hWnd = createWin32Window();
        GEventBus->subscribe<CEventWindowInputKeyboard>(&CBaseWindow::updateKeysState);
        GEventBus->subscribe<CEventWindowInputMouseButton>(&CBaseWindow::updateKeysState);
    }

    Windows::CBaseWindow::~CBaseWindow() {
        if (_hWnd) {
            destroyWindow(_hWnd);
        }
    }

    Windows::HWND Windows::CBaseWindow::createWin32Window() {
        auto wnd = createWindowA(_title.cstr(), _pos.x, _pos.y, (TInt32)_size.x, (TInt32)_size.y, E_WINDOW_FLAGS_DEFAULT, CBaseWindow::EventProcedure);
        setWindowLongPtrA(wnd, E_WINDOW_LONG_PTR_NAME_USERDATA, (TPtrAddr)this);
        return wnd;
    }

    void Windows::CBaseWindow::EventProcedure(HWND hWnd, const SWindowEventData& e) {

        static Point2i lastMousePos = {};
        
        switch (e.type) {
            case E_WINDOW_EVENT_CLOSE: {
                GEventBus->fire(CEventWindowClose{});
            } break;
            case E_WINDOW_EVENT_ENTER_FOCUS: {
                GEventBus->fire(CEventWindowGotFocus());
            } break;
            case E_WINDOW_EVENT_EXIT_FOCUS: {
                GEventBus->fire(CEventWindowLostFocus());
            } break;
            case E_WINDOW_EVENT_MOVE: {

            } break;
            case E_WINDOW_EVENT_RESIZE: {
                const auto& size = e.onResize;
                GEventBus->fire(CEventWindowResized({(TReal)size.width, (TReal)size.height}));
            } break;
            case E_WINDOW_EVENT_MOUSE_MOVE: {
                const auto& mpos = Point2i{ (TInt32)e.onMouseMove.x, (TInt32)e.onMouseMove.y };
                GEventBus->fire(CEventWindowInputMouseMoved(mpos, lastMousePos));

            } break;
            case E_WINDOW_EVENT_KEY_PRESSED:
            case E_WINDOW_EVENT_KEY_RELEASED: {
                const auto& k = e.onKey;
                EKey key = mapKeysFromEVK[k.evk];
                EKeyMod mod = mapModsFromEVK[k.evk];
                // auto& tglState = bw->getKeyboardKeys()[(int32)key];
                // auto& modState = bw->getKeyboardKeysMod()[(int32)key];

                GEventBus->fire(CEventWindowInputKeyboard(key, mod, k.isPressed));

                // //if (tglState == EToggleState::E_TOGGLE_STATE_RELEASED) {
                // //    tglState = EToggleState::E_TOGGLE_STATE_IDLE;
                // //}
                // tglState = k.isPressed ? E_TOGGLE_STATE_PRESSED : E_TOGGLE_STATE_RELEASED;
                // modState = mapModsFromEVK[k.evk];

            } break;
            case E_WINDOW_EVENT_MOUSE_PRESSED:
            case E_WINDOW_EVENT_MOUSE_RELEASED: {
                const auto& ms = e.onMouse;
                EKey key = mapKeysFromEVK[ms.evk == 16 ? ms.evk - 1 : ms.evk];
                EMouseButton btn = mapModsFromEVK[ms.evk];
                GEventBus->fire(CEventWindowInputMouseButton(lastMousePos, btn, ms.isPressed));
            } break;


            default: break;
        }
    }

    void Windows::CBaseWindow::updateKeysState(const CEventWindowInputKeyboard& e) {
        _keysStates[TInt32(e.getKey())] = e.isPressed() ? E_TOGGLE_STATE_PRESSED : E_TOGGLE_STATE_RELEASED;
        _keysModes[TInt32(e.getKey())] = EKeyMod(e.getKeyMod());
    }

    void Windows::CBaseWindow::updateKeysState(const CEventWindowInputMouseButton& e) {
        _keysStates[TInt32(e.getButton())] = e.isPressed() ? E_TOGGLE_STATE_PRESSED : E_TOGGLE_STATE_RELEASED;
    }

    void Windows::CBaseWindow::update() {
        static TUint32 tickCount = 0;
        if (tickCount > 30) {
            for (TUint8 i = 0; i < _releasedKeysCount; ++i) {
                _keysStates[_releasedKeys[i]] = E_TOGGLE_STATE_IDLE;
            }
            _releasedKeysCount = 0;
            tickCount = 0;
        }
        tickCount++;
        peekWindowMessagesA(_hWnd);
    }

    bool Windows::CBaseWindow::isOpen() const {
        return _hWnd != nullptr;
    }

    void Windows::CBaseWindow::setFullscreen(bool enable) {
        if (enable) {
            setWindowLongPtrA(_hWnd, E_WINDOW_LONG_PTR_NAME_STYLE, E_WINDOW_FLAGS_BORDERLESS);
            showWindow(_hWnd, E_WINDOW_SHOW_FLAGS_MAXIMIZED);
        }
        else {
            setWindowLongPtrA(_hWnd, E_WINDOW_LONG_PTR_NAME_STYLE, E_WINDOW_FLAGS_DEFAULT);
            showWindow(_hWnd, E_WINDOW_SHOW_FLAGS_NORMAL);
        }
    }

    void Windows::CBaseWindow::setTitle(const CString& title) {
        setWindowTextA(_hWnd, title.cstr());
    }

    void Windows::CBaseWindow::setMaximized(bool enable) {
        showWindow(_hWnd, enable ? E_WINDOW_SHOW_FLAGS_MAXIMIZED : E_WINDOW_SHOW_FLAGS_NORMAL);
    }

    void Windows::CBaseWindow::suspend(bool enable) {
        showWindow(_hWnd, enable ? E_WINDOW_SHOW_FLAGS_HIDDEN : E_WINDOW_SHOW_FLAGS_NORMAL);
    }

    void* Windows::CBaseWindow::getNativeHandle() const {
        return _hWnd;
    }

    EToggleState* Windows::CBaseWindow::getKeyboardKeys() {
        return _keysStates;
    }

    EKeyMod* Windows::CBaseWindow::getKeyboardKeysMod() {
        return _keysModes;
    }

    void Windows::CBaseWindow::addReleasedKey(EKey key) {
        _releasedKeys[_releasedKeysCount++] = (TInt32)key;
    }

    void Windows::CBaseWindow::setPos(const Point2i& p) {
        _pos = p;
    }

    void Windows::CBaseWindow::setSize(const FVec2& s) {
        _size = s;
    }

}
