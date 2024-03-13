#include <Platform/Linux/LinuxPlatformKeyboard.h>

#if NW_OS(LINUX)

namespace Neowise::Platform::Linux {
    void CKeyboard::getGlobalState(EToggleState keysToggleState[CInputDevice::kMaxToggleStates],
								   EKeyMod keysModifiedState[CInputDevice::kMaxToggleStates]) 
    {}

}

#endif
