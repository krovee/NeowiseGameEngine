#pragma once

#include <Base/Templated.h>
#include <Input/Keycode.h>

namespace Neowise {
    class CBaseWindow;

    /** 
    * State of any key of input device.  
    */
    enum EToggleState : TUint8 {
        E_TOGGLE_STATE_IDLE		= 0x0000,
        E_TOGGLE_STATE_RELEASED	= 0x0001,
        E_TOGGLE_STATE_PRESSED	= 0x0002,
    };

    /** 
    * Static kind of input device.
    */
    enum EInputDevice : TUint8 {
        E_INPUT_DEVICE_UNDEFINED,
        E_INPUT_DEVICE_KEYBOARD,
        E_INPUT_DEVICE_MOUSE
    };

    /** 
    * Generic class for any input device. 
    */
    class NW_API CInputDevice {
    public:
         static const TUint64 kMaxToggleStates = 512;

         constexpr CInputDevice(EInputDevice kind) 
             : _kind(kind) 
         {}

         TBool isKeyPressed(EKey key, EKeyMod mod = E_KEY_MOD_ANY) const;
         TBool isKeyReleased(EKey key, EKeyMod mod = E_KEY_MOD_ANY) const;
         TBool isKeyClicked(EKey key, EKeyMod mod = E_KEY_MOD_ANY) const;
         TBool isKeysPressed(TInitializerList<EKey> keys, EKeyMod mod = E_KEY_MOD_ANY) const;
         TReal getX() const;
         TReal getY() const;
         TReal getZ() const;

         EInputDevice getKind() const;
         void reset();
    protected:
        virtual void updateState(CBaseWindow*) = 0;

    protected:
        EToggleState*	_keysStates = {};
        EKeyMod*		_keysModes  = {};
        TReal			_axis[3] = {};
        EInputDevice	_kind = E_INPUT_DEVICE_UNDEFINED;
    };
}
