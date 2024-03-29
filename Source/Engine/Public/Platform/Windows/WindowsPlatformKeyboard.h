#pragma once

#include "WindowsBase.h"
#include <Input/InputDevice.h>

namespace Neowise::Platform::Windows {
	class NW_API CKeyboard {
	public:
		static void getGlobalState(EToggleState keysToggleState[CInputDevice::kMaxToggleStates],
			EKeyMod keysModifiedState[CInputDevice::kMaxToggleStates]);

		static EKey TranslateEVK(uint64 vki, EKeyMod& mod);
	};
}
