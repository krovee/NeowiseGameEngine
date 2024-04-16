#pragma once

#include <Engine/Events/Event.h>

namespace Neowise {
    
    class CEventBus {
    public:
        constexpr static TUint kMaxSubscribers = 16;
        using StorageHT = HT<EventID, TStaticVector<IEventHandlerWrapper, kMaxSubscribers>>;

        void subscribe(IEventHandlerWrapper handler);

        void fire(const CEvent& e);

        template<class T>
        void fire(const T& event) {
            fire(static_cast<const CEvent&>(event));
        }

        template<class T>
        void subscribe(IEventHandlerWrapper handler) {
            subscribe(handler);
        }

        template<class T>
        void subscribe(const typename CEventHandlerWrapper<T>::Handler& handler) {
            subscribe(makeEventHandler<T>(handler));
        }
    private:
        StorageHT categorizedSubscribers = {};
    };
}
