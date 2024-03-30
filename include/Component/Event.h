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
    Collision,
    Undefined

};

 class CollisionData {
 public:

     CollisionData();
    CollisionData(int entityUID1, int entityUID2, float velX1, float velY1, float velX2, float velY2) {
        entity1UID = entityUID1;
        entity2UID = entityUID2;
        velX1 = velX1;
        velX2 = velX2;
        velY1 = velY1;
        velY2 = velY2;
    }
    int entity1UID;
    int entity2UID;
    float velX1, velY1; // Velocity of entity 1
    float velX2, velY2; // Velocity of entity 2
    // Additional collision properties (if needed)
};

using EventData = std::variant<std::array<float, 2>, char, SDL_Scancode, CollisionData>;


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
