#include <Input/InputSystem.h>

namespace Neowise {
    void CInputSystem::addDevice(CInputDevice &device) {
        _devices.pushBack(&forward<CInputDevice&>(device));
    }

    void CInputSystem::update(CBaseWindow* pwnd) {
        for (auto dev : _devices) {
            // call to reset internal state
            dev->reset();
            switch (dev->getKind()) {
                case E_INPUT_DEVICE_KEYBOARD: {
                    CKeyboardInputDevice* kbd = reinterpret_cast<CKeyboardInputDevice*>(dev);
                    kbd->updateState(pwnd);
                } break;
                case E_INPUT_DEVICE_MOUSE: {
                    CMouseInputDevice* ms = reinterpret_cast<CMouseInputDevice*>(dev);
                    ms->updateState(pwnd);
                } break;
                default: break;
            }
        }
    }

}
