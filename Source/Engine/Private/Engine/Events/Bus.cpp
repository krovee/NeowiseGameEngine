#include <Engine/Events/Bus.h>

namespace Neowise {
    CEventBus* GEventBus = nullptr;

    void CEventBus::subscribe(IEventHandlerWrapper handler) {
        const auto eid = handler->getID();

        if (!categorizedSubscribers.get(eid)) {
            categorizedSubscribers.emplace(eid);
        }

        auto subscribers = categorizedSubscribers.get(eid);
        if (subscribers) {
            subscribers.unwrap().emplace(handler);
        }
    }

    void CEventBus::fire(const CEvent& e) {
        const auto eid = e.getEventID();

        auto subscribers = categorizedSubscribers.get(eid);
        if (subscribers) {
            auto& handlers = subscribers.unwrap();
            for (auto& handler : handlers) {
                handler->exec(e);
            }
        }
    }

}
