#include "Math/Point.h"
#include <Engine/EngineEvents.h>

namespace Neowise {
    const Point2i& CEventWindowMoved::getPos() const {
        return _pos;
    }

    TInt32 CEventWindowMoved::getX() const {
        return _pos.x;
    }

    TInt32 CEventWindowMoved::getY() const {
        return _pos.y;
    }


    const FVec2& CEventWindowResized::getSize() const {
        return _size;
    }

    TReal CEventWindowResized::getWidth() const {
        return _size.x;
    }

    TReal CEventWindowResized::getHeight() const {
        return _size.y;
    }


    TUint8 CEventWindowInputKeyboard::getKey() const {
        return key;
    }

    TUint8 CEventWindowInputKeyboard::getKeyMod() const {
        return keyMod;
    }

    TBool CEventWindowInputKeyboard::isPressed() const {
        return pressed;
    }


    TUint8 CEventWindowInputMouseMoved::getMouseId() const {
        return _mid;
    }

    const Point2i& CEventWindowInputMouseMoved::getPos() const {
        return _pos;
    }

    TInt32 CEventWindowInputMouseMoved::getX() const {
        return _pos.x;
    }

    TInt32 CEventWindowInputMouseMoved::getY() const {
        return _pos.y;
    }

    const Point2i& CEventWindowInputMouseMoved::getDelta() const {
        return _deltaPos;
    }

    TInt32 CEventWindowInputMouseMoved::getDeltaX() const {
        return _deltaPos.x;
    }

    TInt32 CEventWindowInputMouseMoved::getDeltaY() const {
        return _deltaPos.y;
    }


    TUint8 CEventWindowInputMouseButton::getMouseId() const {
        return _mid;
    }

    const Point2i& CEventWindowInputMouseButton::getPos() const {
        return _pos;
    }

    TInt32 CEventWindowInputMouseButton::getX() const {
        return _pos.x;
    }

    TInt32 CEventWindowInputMouseButton::getY() const {
        return _pos.y;
    }

    TUint8 CEventWindowInputMouseButton::getButton() const {
        return _buttonKey;
    }

    TBool CEventWindowInputMouseButton::isPressed() const {
        return _pressed;
    }
}
