#include <Platform/Null/NullPlatformKeyboard.h>

namespace Neowise::Platform::Null {
	void CKeyboard::getGlobalState(EToggleState keysToggleState[CInputDevice::kMaxToggleStates],
		EKeyMod keysModifiedState[CInputDevice::kMaxToggleStates]) 
	{}
}
