#include "Engine/EngineEvents.h"
#include "Input/InputDevice.h"
#include <Platform/Linux/LinuxPlatformWindow.h>

#include <Platform/Linux/LinuxBase.h>
#include <Engine/Events/Bus.h>
#include <Engine/EngineLoop.h>
#include <Base/BuildVersion.h>

namespace Neowise::Platform::Linux {

    CBaseWindow::CBaseWindow(defaultCreateTag) 
    : Neowise::CBaseWindow({0, 0}, {1280, 720}, false, true, false, true)
    {
        CStringBuilder s(_title);
        s << "Neowise Engine (build." << uint(buildVersion) << ")";
        const auto ret = _WindowCreate(_id, _title, _pos, _size);
        if (ret) {
            switch (ret) {
                case E_WINDOW_ERROR_X_MISSING: {
                    GDiag << "Failed to create a window due to X11 missing display!\n";
                    GEngineLoop->requestExit(173);
                } break;
                case E_WINDOW_ERROR_INVALID_ARGUMENTS: {
                    GDiag << "Failed to create a window due to bad arguments!\n";
                    GEngineLoop->requestExit(172);
                } break;
                case E_WINDOW_ERROR_BAD_FLUSH: {
                    GDiag << "Failed to create a window due to bad flush!\n";
                    GEngineLoop->requestExit(171);
                } break;

                default: break;
            }
        }

        GEventBus->subscribe<CEventWindowInputKeyboard>(&CBaseWindow::updateKeysState);
        GEventBus->subscribe<CEventWindowInputMouseButton>(&CBaseWindow::updateKeysState);

    }

    CBaseWindow::~CBaseWindow() {
        _WindowDestroy(_id);
    }

    void CBaseWindow::update() {
        if (_dirty) {
            _WindowSetPlacement(_id, _pos, _size);
            _dirty = false;
        }
        _WindowInputInfo inputInfo = {};
        inputInfo.pKeyMods = _keysModes;
        inputInfo.pKeysState = _keysStates;

        _WindowPumpMessages(_id, &inputInfo);
    }

    bool CBaseWindow::isOpen() const {
        return _id != _WindowID(-1);
    }

    void CBaseWindow::setFullscreen(bool value) {
        NW_UNUSED(value);
    }

    void CBaseWindow::setTitle(const CString& title) {
        _WindowSetTitle(_id, title);
    }

    void CBaseWindow::setMaximized(bool value) {
        NW_UNUSED(value);
    }

    void CBaseWindow::suspend(bool value) {
        NW_UNUSED(value);
    }

    void* CBaseWindow::getNativeHandle() const {
        return (void *)(&_id);
    }

    EToggleState* CBaseWindow::getKeyboardKeys() {
        return _keysStates;
    }

    EKeyMod* CBaseWindow::getKeyboardKeysMod() {
        return _keysModes;
    }

    void CBaseWindow::addReleasedKey(EKey key) {
        _releasedKeys[_releasedKeysCount++] = key;
    }

    void CBaseWindow::setPos(const Point2i& p) {
        _dirty = true;
        _pos = p;
    }

    void CBaseWindow::setSize(const FVec2& s) {
        _dirty = true;
        _size = s;
    }

    void CBaseWindow::updateKeysState(const CEventWindowInputKeyboard& e) {
        _keysStates[int32(e.getKey())] = e.isPressed() ? E_TOGGLE_STATE_PRESSED : E_TOGGLE_STATE_RELEASED;
        _keysModes[int32(e.getKey())] = EKeyMod(e.getKeyMod());
    }

    void CBaseWindow::updateKeysState(const CEventWindowInputMouseButton& e) {
        _keysStates[int32(e.getButton())] = e.isPressed() ? E_TOGGLE_STATE_PRESSED : E_TOGGLE_STATE_RELEASED;
    }

}
