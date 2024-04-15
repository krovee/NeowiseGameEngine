#include <Input/InputSystem.h>

#include <Platform/PlatformKeyboard.h>
#include <Platform/PlatformWindow.h>

namespace Neowise {
    void CKeyboardInputDevice::updateState(CBaseWindow* pwnd) {
        Platform::CBaseWindow* plat = (Platform::CBaseWindow*)pwnd;
        _keysStates = plat->getKeyboardKeys();
        _keysModes = plat->getKeyboardKeysMod();
    }

}
