#include "Math/Point.h"
#include <Engine/EngineEvents.h>

namespace Neowise {
    const Point2i& CEventWindowMoved::getPos() const {
        return _pos;
    }

    int32 CEventWindowMoved::getX() const {
        return _pos.x;
    }

    int32 CEventWindowMoved::getY() const {
        return _pos.y;
    }


    const FVec2& CEventWindowResized::getSize() const {
        return _size;
    }

    real CEventWindowResized::getWidth() const {
        return _size.x;
    }

    real CEventWindowResized::getHeight() const {
        return _size.y;
    }


    uint8 CEventWindowInputKeyboard::getKey() const {
        return key;
    }

    uint8 CEventWindowInputKeyboard::getKeyMod() const {
        return keyMod;
    }

    bool CEventWindowInputKeyboard::isPressed() const {
        return pressed;
    }


    uint8 CEventWindowInputMouseMoved::getMouseId() const {
        return _mid;
    }

    const Point2i& CEventWindowInputMouseMoved::getPos() const {
        return _pos;
    }

    int32 CEventWindowInputMouseMoved::getX() const {
        return _pos.x;
    }

    int32 CEventWindowInputMouseMoved::getY() const {
        return _pos.y;
    }

    const Point2i& CEventWindowInputMouseMoved::getDelta() const {
        return _deltaPos;
    }

    int32 CEventWindowInputMouseMoved::getDeltaX() const {
        return _deltaPos.x;
    }

    int32 CEventWindowInputMouseMoved::getDeltaY() const {
        return _deltaPos.y;
    }


    uint8 CEventWindowInputMouseButton::getMouseId() const {
        return _mid;
    }

    const Point2i& CEventWindowInputMouseButton::getPos() const {
        return _pos;
    }

    int32 CEventWindowInputMouseButton::getX() const {
        return _pos.x;
    }

    int32 CEventWindowInputMouseButton::getY() const {
        return _pos.y;
    }

    uint8 CEventWindowInputMouseButton::getButton() const {
        return _buttonKey;
    }

    bool CEventWindowInputMouseButton::isPressed() const {
        return _pressed;
    }
}
