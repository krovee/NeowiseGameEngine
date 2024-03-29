#include <Platform/Windows/WindowsPlatformWindow.h>

#include <Engine/EngineGlobals.h>
#include <Base/BuildVersion.h>

namespace Neowise::Platform {
	namespace {
        wchar_t* itoa(uint64 value, wchar_t* result, int base) {
            if (base < 2 || base > 36) { *result = '\0'; return result; }

            wchar_t* ptr = result, * ptr1 = result, tmp_char;
            uint64 tmp_value;

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
				real(Windows::getPrimaryMonitorWidth()),
				real(Windows::getPrimaryMonitorHeight())
			};
			return screenSize;
		}
	} // 8

	Windows::CBaseWindow::CBaseWindow(defaultCreateTag) 
	: Neowise::CBaseWindow({0, 0}, sGetScreenSize() / 2, false, true, false, true)
	{
        CStringBuilder s(_title);
        s << "Neowise Engine (build." << uint(buildVersion) << ")";
        _hWnd = createWin32Window();
	}

	Windows::CBaseWindow::~CBaseWindow() {
        if (_hWnd) {
            destroyWindow(_hWnd);
        }
	}

    Windows::HWND Windows::CBaseWindow::createWin32Window() {
        auto wnd = createWindowA(_title.cstr(), _pos.x, _pos.y, (int32)_size.x, (int32)_size.y, E_WINDOW_FLAGS_DEFAULT, CBaseWindow::EventProcedure);
        setWindowLongPtrA(wnd, E_WINDOW_LONG_PTR_NAME_USERDATA, (ptraddr)this);
        return wnd;
    }

    void Windows::CBaseWindow::EventProcedure(HWND hWnd, const SWindowEventData& e) {
        Windows::CBaseWindow* bw = (Windows::CBaseWindow*)getWindowLongPtrA(hWnd, E_WINDOW_LONG_PTR_NAME_USERDATA);
        if (!bw) return;

        switch (e.type) {
            case E_WINDOW_EVENT_CLOSE: {
                GIsExitRequested = true;
                GExitRequestCode = 1;
            } break;
            case E_WINDOW_EVENT_ENTER_FOCUS: {
                
            } break;
            case E_WINDOW_EVENT_EXIT_FOCUS: {

            } break;
            case E_WINDOW_EVENT_MOVE: {
                const auto& pos = e.onMove;
                bw->setPos({ pos.x, pos.y });
            } break;
            case E_WINDOW_EVENT_RESIZE: {
                const auto& size = e.onResize;
                bw->setSize({ (real)size.width, (real)size.height });
            } break;
            case E_WINDOW_EVENT_MOUSE_MOVE: {
                const auto& mpos = e.onMouseMove;

            } break;
            case E_WINDOW_EVENT_KEY_PRESSED:
            case E_WINDOW_EVENT_KEY_RELEASED: {
                const auto& k = e.onKey;
                EKey key = mapKeysFromEVK[k.evk];
                auto& tglState = bw->getKeyboardKeys()[(int32)key];
                auto& modState = bw->getKeyboardKeysMod()[(int32)key];

                //if (tglState == EToggleState::E_TOGGLE_STATE_RELEASED) {
                //    tglState = EToggleState::E_TOGGLE_STATE_IDLE;
                //}
                tglState = k.isPressed ? E_TOGGLE_STATE_PRESSED : E_TOGGLE_STATE_RELEASED;
                modState = mapModsFromEVK[k.evk];

                if (!k.isPressed) {
                    bw->addReleasedKey(key);
                }

            } break;
            case E_WINDOW_EVENT_MOUSE_PRESSED:
            case E_WINDOW_EVENT_MOUSE_RELEASED: {
                const auto& ms = e.onMouse;

            } break;

            default: break;
        }
    }

    void Windows::CBaseWindow::update() {
        static uint32 tickCount = 0;
        if (tickCount > 30) {
            for (uint8 i = 0; i < _releasedKeysCount; ++i) {
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
        _releasedKeys[_releasedKeysCount++] = (int32)key;
    }

    void Windows::CBaseWindow::setPos(const Point2i& p) {
        _pos = p;
    }

    void Windows::CBaseWindow::setSize(const FVec2& s) {
        _size = s;
    }

}
