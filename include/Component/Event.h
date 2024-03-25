//
// Created by Jacob Ross on 3/24/24.
//

#ifndef BLOOM_ENGINE_EVENT_H
#define BLOOM_ENGINE_EVENT_H

#include <array>
#include "Component.h"
#include "SDL.h"

enum class EventType {
    InputKeyDown,
    InputKeyUp,
    Physics,
    Undefined,

};

using EventData = std::variant<std::array<float, 2>, char, SDL_Scancode>;


class Event : public Component {
public:
    Event() {
        type = "Event";
        entityUID = {};
        eventType = EventType::Undefined;
        eventData = {};
    }
    Event(EventType newEventType, const EventData& payload) {
        type = "Event";
        entityUID={};
        eventType = newEventType;
        eventData = payload;
    }

    Event(int UID, EventType newEventType, const EventData& payload) {
        type = "Event";
        entityUID = UID;
        eventType = newEventType;
        eventData = payload;
    }


    EventType eventType;
    //float deltaTime;
    int entityUID;
    EventData eventData;


};

#endif //BLOOM_ENGINE_EVENT_H
