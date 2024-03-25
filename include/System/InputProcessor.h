//
// Created by Jacob Ross on 3/24/24.
//

#ifndef BLOOM_ENGINE_INPUTPROCESSOR_H
#define BLOOM_ENGINE_INPUTPROCESSOR_H

#include "../Entity/Entity.h"
#include "EntityManager.h"
#include "Dispatcher.h"
#include "../Component/ComponentTypes.h"
#include "../Component/Event.h"
#include "../Component/Player.h"
#include "../Component/Transform.h"
#include "../Component/Physics.h"

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
