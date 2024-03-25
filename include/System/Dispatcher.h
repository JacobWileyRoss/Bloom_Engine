//
// Created by Jacob Ross on 3/24/24.
//

#ifndef BLOOM_ENGINE_DISPATCHER_H
#define BLOOM_ENGINE_DISPATCHER_H

#include <functional>
#include "../Component/Event.h"
#include "EntityManager.h"


class Dispatcher {
public:
    Dispatcher(EntityManager& entityManager) : entityManager(entityManager) {};
    using EventCallback = std::function<void(const Event&)>;

    void addEventListener(EventType eventType, const EventCallback& callback);

    void dispatchEvent(const Event& event);


private:
    EntityManager entityManager;
    std::unordered_map<EventType, std::vector<EventCallback>> listeners;

};

#endif //BLOOM_ENGINE_DISPATCHER_H
