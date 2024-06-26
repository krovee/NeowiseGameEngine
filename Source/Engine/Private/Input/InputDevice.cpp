#include <Input/InputDevice.h>
#include <Base/MemoryUtilities.h>

namespace Neowise {
    TBool CInputDevice::isKeyPressed(EKey key, EKeyMod mod) const {
        return 
            _keysStates[TInt32(key)] == E_TOGGLE_STATE_PRESSED && 
            _keysModes[TInt32(key)] == mod
        ;
    }

    TBool CInputDevice::isKeyReleased(EKey key, EKeyMod mod) const {
        return
            _keysStates[TInt32(key)] == E_TOGGLE_STATE_RELEASED &&
            _keysModes[TInt32(key)] == mod
            ;
    }

    TBool CInputDevice::isKeyClicked(EKey key, EKeyMod mod) const {
        /*
        * Clicked key is really just a E_TOGGLE_STATE_RELEASED key. Because if you'll
        * think about it, you'd find out every E_TOGGLE_STATE_RELEASED key button was
        * E_TOGGLE_STATE_PRESSED somehow, or anyway 'clicked'.
        */
        return isKeyReleased(key, mod);
    }

    TBool CInputDevice::isKeysPressed(TInitializerList<EKey> keys, EKeyMod mod) const {
        TUint8 count = 0;
        for (auto&& key : keys) {
            if (_keysStates[TInt32(key)] == E_TOGGLE_STATE_PRESSED && _keysModes[TInt32(key)] == mod)
                count++;
        }
        return count == keys.size();
    }

    TReal CInputDevice::getX() const {
        return _axis[0];
    }

    TReal CInputDevice::getY() const {
        return _axis[1];
    }

    TReal CInputDevice::getZ() const {
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
