//
// Created by Jacob Ross on 3/24/24.
//

#ifndef BLOOM_ENGINE_INPUTPROCESSOR_H
#define BLOOM_ENGINE_INPUTPROCESSOR_H

#include "Entity.h"
#include "EntityManager.h"
#include "Dispatcher.h"
#include "ComponentTypes.h"
#include "Event.h"
#include "Player.h"
#include "Transform.h"
#include "Physics.h"

class InputProcessor {
public:
    explicit InputProcessor(EntityManager& entityManager, Dispatcher& dispatcher)
            : entityManager(entityManager), dispatcher(dispatcher) {}
    void ProcessInput(SDL_Event& event);

private:
    EntityManager& entityManager;
    Dispatcher& dispatcher;
    EventData eventData;

};


#endif //BLOOM_ENGINE_INPUTPROCESSOR_H
