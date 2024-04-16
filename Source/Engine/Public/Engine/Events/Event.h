#pragma once

#include <Base/Common.h>

#ifndef NW_EVENT_DECLARATION
#   define NW_EVENT_DECLARATION(_typename_)                                         \
    public:                                                                         \
        static EventID  getStaticEventID() { return sEventName.getCRC(); }          \
        EventID         getEventID() const override { return getStaticEventID(); }  \
    private:                                                                        \
        static inline const CString sEventName = #_typename_;
#endif

namespace Neowise {

    using EventID = TUint;

    class NW_API CEvent {
    public:
        virtual ~CEvent() = default;

        virtual EventID getEventID() const = 0;
        
        TBool isHandled() const;
        void markHandled();
    private:
        TBool handled = kFalse;
    };

    template<class T>
    using TEventHandler = void(*)(const T&);

    class NW_API CEventHandlerWrapperInterface {
    public:
        virtual ~CEventHandlerWrapperInterface() = default;

        void exec(const CEvent& e) {
            docall(e);
        }

        virtual EventID getID() const { return -1; }

    private:
        virtual void docall(const CEvent& e) = 0;
    };

    using IEventHandlerWrapper = CEventHandlerWrapperInterface*;

    template<class T>
    struct EventHandlerSlot {
        using Handler = TEventHandler<T>;

        const Handler&  handler;
        
        EventID getID() const {
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

        EventID getID() const override { 
            return _handlerID;
        }
    private:
        void docall(const CEvent& e) override {
            if (e.getEventID() == T::getStaticEventID()) {
                _handler(static_cast<const T&>(e));
            }
        }

    private:
        Handler         _handler;
        const EventID   _handlerID;
    };

    template<class T>
    using TEventHandlerWrapper = CEventHandlerWrapper<T>*;

    template<class T>
    constexpr IEventHandlerWrapper makeEventHandler(const typename CEventHandlerWrapper<T>::Handler& evFunc) {
        auto p = reinterpret_cast<TEventHandlerWrapper<T>>(GAlloc->allocate(sizeof(CEventHandlerWrapper<T>)));
        construct_at(*p, evFunc);
        return reinterpret_cast<IEventHandlerWrapper>(p);
    }

}
