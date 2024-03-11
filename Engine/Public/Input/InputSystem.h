#pragma once

#include <Base/StaticVector.h>
#include "InputDevice.h"

namespace Neowise {
	class CBaseWindow;

	/** 
	* Specialized for E_INPUT_DEVICE_KEYBOARD input device class.
	*/
	class NW_API CKeyboardInputDevice : public CInputDevice {
	public:
		constexpr CKeyboardInputDevice() : CInputDevice(E_INPUT_DEVICE_KEYBOARD)
		{}

		void updateState(CBaseWindow* pwnd) override;
	};

	/** 
	* 
	*/
	class NW_API CMouseInputDevice : public CInputDevice {
	public:
		constexpr CMouseInputDevice() : CInputDevice(E_INPUT_DEVICE_MOUSE) 
		{}

		void updateState(CBaseWindow* pwnd) override;
	};

	/** 
	* 
	*/
	class NW_API CInputSystem {
	public:
		static const uint64 kMaxInputDevices = 8;

		void addDevice(CInputDevice& device);
		void update(CBaseWindow* p);
	private:
		CStaticVector<CInputDevice*, kMaxInputDevices>	_devices = {};
	};
}
