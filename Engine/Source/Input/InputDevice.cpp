#include <Input/InputDevice.h>
#include <Base/MemoryUtilities.h>

namespace Neowise {
	bool CInputDevice::isKeyPressed(EKey key, EKeyMod mod) const {
		return 
			_keysStates[int32(key)] == E_TOGGLE_STATE_PRESSED && 
			_keysModes[int32(key)] == mod
		;
	}

	bool CInputDevice::isKeyReleased(EKey key, EKeyMod mod) const {
		return
			_keysStates[int32(key)] == E_TOGGLE_STATE_RELEASED &&
			_keysModes[int32(key)] == mod
			;
	}

	bool CInputDevice::isKeyClicked(EKey key, EKeyMod mod) const {
		/*
		* Clicked key is really just a E_TOGGLE_STATE_RELEASED key. Because if you'll
		* think about it, you'd find out every E_TOGGLE_STATE_RELEASED key button was
		* E_TOGGLE_STATE_PRESSED somehow, or anyway 'clicked'.
		*/
		return isKeyReleased(key, mod);
	}

	bool CInputDevice::isKeysPressed(TInitializerList<EKey> keys, EKeyMod mod) const {
		uint8 count = 0;
		for (auto&& key : keys) {
			if (_keysStates[int32(key)] == E_TOGGLE_STATE_PRESSED && _keysModes[int32(key)] == mod)
				count++;
		}
		return count == keys.size();
	}

	real CInputDevice::getX() const {
		return _axis[0];
	}

	real CInputDevice::getY() const {
		return _axis[1];
	}

	real CInputDevice::getZ() const {
		return _axis[2];
	}

	EInputDevice CInputDevice::getKind() const {
		return _kind;
	}

	void CInputDevice::reset() {
		if (_keysStates && _keysModes) {
			Memory::clear(_keysStates, sizeof _keysStates);
			Memory::clear(_keysModes, sizeof _keysModes);
		}
	}
}
