#pragma once

#include <Base/Common.h>

#ifndef NW_EVENT_DECLARATION
#   define NW_EVENT_DECLARATION(_typename_)                             \
    public:                                                             \
        static uint getStaticEventID() { return sEventName.getCRC(); }  \
        uint getEventID() const override { return getStaticEventID(); } \
    private:                                                            \
        static inline CString sEventName = #_typename_;
#endif

namespace Neowise {

    class NW_API CEvent {
    public:
        virtual ~CEvent() = default;

        virtual uint getEventID() const = 0;
        
        bool isHandled() const;
        void markHandled();
    private:
        bool handled = false;
    };

    template<class T>
    using TEventHandler = void(*)(const T&);

    class NW_API CEventHandlerWrapperInterface {
    public:
        virtual ~CEventHandlerWrapperInterface() = default;

        void exec(const CEvent& e) {
            docall(e);
        }

        virtual uint getID() const { return -1; }

    private:
        virtual void docall(const CEvent& e) = 0;
    };

    template<class T>
    struct EventHandlerSlot {
        using Handler = TEventHandler<T>;

        const Handler&  handler;
        
        uint getID() const {
            return T::getStaticEventID();
        }

        operator const Handler&() const {
            return handler;
        }

        inline EventHandlerSlot(const Handler& __handler) : handler(forward<const Handler&>(__handler))
        {}
    };

    template<class T>
    class CEventHandlerWrapper : public CEventHandlerWrapperInterface {
    public:
        using Handler   = TEventHandler<T>;
        using Slot      = EventHandlerSlot<T>;

        explicit CEventHandlerWrapper(const Slot& handler) : _handler(handler), _handlerID(handler.getID())
        {}
        virtual ~CEventHandlerWrapper() = default;

        uint getID() const override { 
            return _handlerID;
        }
    private:
        void docall(const CEvent& e) override {
            if (e.getEventID() == T::getStaticEventID()) {
                _handler(static_cast<const T&>(e));
            }
        }

    private:
        Handler     _handler;
        const uint  _handlerID;
    };

}
