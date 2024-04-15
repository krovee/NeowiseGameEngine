#pragma once

#include <Engine/Events/Event.h>

namespace Neowise {

    class CEventWindowClose : public CEvent {
        NW_EVENT_DECLARATION(CEventWindowClose)
    };

    class CEventWindowSuspended : public CEvent {
        NW_EVENT_DECLARATION(CEventWindowSuspended)
    };

    class CEventWindowGotFocus : public CEvent {
        NW_EVENT_DECLARATION(CEventWindowGotFocus)
    };
    
    class CEventWindowLostFocus : public CEvent {
        NW_EVENT_DECLARATION(CEventWindowLostFocus)
    };

    class CEventWindowMoved : public CEvent {
        NW_EVENT_DECLARATION(CEventWindowMoved)
    public:
        constexpr CEventWindowMoved(const Point2i& pos) : _pos(pos)
        {}

        const Point2i& getPos() const;

        TInt32 getX() const;
        TInt32 getY() const;
    private:
        const Point2i& _pos;
    };

    class CEventWindowResized : public CEvent {
        NW_EVENT_DECLARATION(CEventWindowResized)
    public:
        constexpr CEventWindowResized(const FVec2& size) : _size(size)
        {}

        const FVec2& getSize() const;

        TReal getWidth() const;
        TReal getHeight() const;
    private:
        const FVec2& _size;
    };

    class CEventWindowInputKeyboard : public CEvent {
        NW_EVENT_DECLARATION(CEventWindowInputKeyboard)
    public:
        constexpr CEventWindowInputKeyboard(const TUint8 _key, const TUint8 _mod, const bool _pressed) : key(_key), keyMod(_mod), pressed(_pressed)
        {}

        TUint8 getKey() const;
        TUint8 getKeyMod() const;
        bool isPressed() const; 
    private:
        const TUint8 key = 0; 
        const TUint8 keyMod = 0; 
        const bool pressed = false; 
    };

    class CEventWindowInputMouseMoved : public CEvent {
        NW_EVENT_DECLARATION(CEventWindowInputMouseMoved)
    public:
        constexpr CEventWindowInputMouseMoved(const Point2i& to, const Point2i& from) : _deltaPos(to - from), _pos(to)
        {}

        constexpr CEventWindowInputMouseMoved(const Point2i& to, const Point2i& from, const TUint8 mouseId) : _deltaPos(to - from), _pos(to), _mid(mouseId)
        {}

        TUint8 getMouseId() const;

        const Point2i& getPos() const;

        TInt32 getX() const;
        TInt32 getY() const;

        const Point2i& getDelta() const;

        TInt32 getDeltaX() const;
        TInt32 getDeltaY() const;
    private:
        const Point2i   _deltaPos;
        const Point2i&  _pos;
        const TUint8     _mid = 0;
    };

    class CEventWindowInputMouseButton : public CEvent {
        NW_EVENT_DECLARATION(CEventWindowInputMouseButton)
    public:
        constexpr CEventWindowInputMouseButton(const Point2i& pos, const TUint8 mod, const bool pressed) : _pos(pos), _buttonKey(mod), _pressed(pressed)
        {}

        constexpr CEventWindowInputMouseButton(const Point2i& pos, const TUint8 mod, const bool pressed, const TUint8 mouseId)
            : _pos(pos), _buttonKey(mod), _pressed(pressed), _mid(mouseId)
        {}

        TUint8 getMouseId() const;

        const Point2i& getPos() const;

        TInt32 getX() const;
        TInt32 getY() const;

        TUint8 getButton() const;
        bool isPressed() const; 
    private:
        const Point2i&  _pos;
        const TUint8     _buttonKey = 0;
        const bool      _pressed = false;
        const TUint8     _mid = 0;
    };
}
