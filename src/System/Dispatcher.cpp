//
// Created by Jacob Ross on 3/24/24.
//

#include "../../include/System/Dispatcher.h"


void Dispatcher::addEventListener(EventType eventType, const EventCallback& callback) {
    listeners[eventType].push_back(callback);
}

void Dispatcher::dispatchEvent(const Event& event) {
    EventType eventType = event.eventType;
    if (event.entityUID) {
        entityManager.entities.find(event.entityUID);
    }
    if (listeners.find(eventType) != listeners.end()) {
        for (const auto& callback : listeners[eventType]) {
            callback(event);
        }
    } else {
        std::cout << "No listeners registered for event type: " << static_cast<int>(eventType) << std::endl;
    }
}
