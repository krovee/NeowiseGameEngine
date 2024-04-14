#pragma once

#include <Base/NumericTypes.h>
#include <Input/InputDevice.h>

namespace Neowise::Platform::Null {
    class NW_API CKeyboard {
    public: 
        static void getGlobalState(EToggleState keysToggleState[CInputDevice::kMaxToggleStates],
                                   EKeyMod keysModifiedState[CInputDevice::kMaxToggleStates]);
    };
}
