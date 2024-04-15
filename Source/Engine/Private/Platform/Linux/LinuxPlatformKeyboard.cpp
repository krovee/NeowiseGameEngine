#include <Platform/Linux/LinuxPlatformKeyboard.h>

namespace Neowise::Platform::Linux {
    void CKeyboard::getGlobalState(EToggleState keysToggleState[CInputDevice::kMaxToggleStates],
                                   EKeyMod keysModifiedState[CInputDevice::kMaxToggleStates]) 
    {
        NW_UNUSED(keysToggleState);
        NW_UNUSED(keysModifiedState);
    }

}
