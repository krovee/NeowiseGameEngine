#pragma once

#include <Base/Templated.h>
#include "Keycode.h"

namespace Neowise {
	class CBaseWindow;

	/** 
	* State of any key of input device.  
	*/
	enum EToggleState : uint8 {
		E_TOGGLE_STATE_IDLE		= 0x0000,
		E_TOGGLE_STATE_RELEASED	= 0x0001,
		E_TOGGLE_STATE_PRESSED	= 0x0002,
	};

	/** 
	* Static kind of input device.
	*/
	enum EInputDevice : uint8 {
		E_INPUT_DEVICE_UNDEFINED,
		E_INPUT_DEVICE_KEYBOARD,
		E_INPUT_DEVICE_MOUSE
	};

	/** 
	* Generic class for any input device. 
	*/
	class NW_API CInputDevice {
	public:
		 static const uint64 kMaxToggleStates = 512;

		 constexpr CInputDevice(EInputDevice kind) 
			 : _kind(kind) 
		 {}

		 bool isKeyPressed(EKey key, EKeyMod mod = E_KEY_MOD_ANY) const;
		 bool isKeyReleased(EKey key, EKeyMod mod = E_KEY_MOD_ANY) const;
		 bool isKeyClicked(EKey key, EKeyMod mod = E_KEY_MOD_ANY) const;
		 bool isKeysPressed(TInitializerList<EKey> keys, EKeyMod mod = E_KEY_MOD_ANY) const;
		 real getX() const;
		 real getY() const;
		 real getZ() const;

		 EInputDevice getKind() const;
		 void reset();
	protected:
		virtual void updateState(CBaseWindow*) = 0;

	protected:
		EToggleState*	_keysStates = {};
		EKeyMod*		_keysModes  = {};
		real			_axis[3] = {};
		EInputDevice	_kind = E_INPUT_DEVICE_UNDEFINED;
	};
}
