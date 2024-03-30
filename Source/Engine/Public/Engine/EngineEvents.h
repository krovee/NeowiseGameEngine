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

        int32 getX() const;
        int32 getY() const;
    private:
        const Point2i& _pos;
    };

    class CEventWindowResized : public CEvent {
        NW_EVENT_DECLARATION(CEventWindowResized)
    public:
        constexpr CEventWindowResized(const FVec2& size) : _size(size)
        {}

        const FVec2& getSize() const;

        real getWidth() const;
        real getHeight() const;
    private:
        const FVec2& _size;
    };

    class CEventWindowInputKeyboard : public CEvent {
        NW_EVENT_DECLARATION(CEventWindowInputKeyboard)
    public:
        constexpr CEventWindowInputKeyboard(const uint8 _key, const uint8 _mod, const bool _pressed) : key(_key), keyMod(_mod), pressed(_pressed)
        {}

        uint8 getKey() const;
        uint8 getKeyMod() const;
        bool isPressed() const; 
    private:
        const uint8 key = 0; 
        const uint8 keyMod = 0; 
        const bool pressed = false; 
    };

    class CEventWindowInputMouseMoved : public CEvent {
        NW_EVENT_DECLARATION(CEventWindowInputMouseMoved)
    public:
        constexpr CEventWindowInputMouseMoved(const Point2i& to, const Point2i& from) : _deltaPos(to - from), _pos(to)
        {}

        constexpr CEventWindowInputMouseMoved(const Point2i& to, const Point2i& from, const uint8 mouseId) : _deltaPos(to - from), _pos(to), _mid(mouseId)
        {}

        uint8 getMouseId() const;

        const Point2i& getPos() const;

        int32 getX() const;
        int32 getY() const;

        const Point2i& getDelta() const;

        int32 getDeltaX() const;
        int32 getDeltaY() const;
    private:
        const Point2i   _deltaPos;
        const Point2i&  _pos;
        const uint8     _mid = 0;
    };

    class CEventWindowInputMouseButton : public CEvent {
        NW_EVENT_DECLARATION(CEventWindowInputMouseButton)
    public:
        constexpr CEventWindowInputMouseButton(const Point2i& pos, const uint8 mod, const bool pressed) : _pos(pos), _buttonKey(mod), _pressed(pressed)
        {}

        constexpr CEventWindowInputMouseButton(const Point2i& pos, const uint8 mod, const bool pressed, const uint8 mouseId)
            : _pos(pos), _buttonKey(mod), _pressed(pressed), _mid(mouseId)
        {}

        uint8 getMouseId() const;

        const Point2i& getPos() const;

        int32 getX() const;
        int32 getY() const;

        uint8 getButton() const;
        bool isPressed() const; 
    private:
        const Point2i&  _pos;
        const uint8     _buttonKey = 0;
        const bool      _pressed = false;
        const uint8     _mid = 0;
    };
}
