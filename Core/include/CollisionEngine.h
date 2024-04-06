//
// Created by Jacob Ross on 3/25/24.
//

#ifndef BLOOM_ENGINE_COLLISIONENGINE_H
#define BLOOM_ENGINE_COLLISIONENGINE_H

#include "EntityManager.h"
#include "Dispatcher.h"
#include "Event.h"
#include "Collider.h"
#include <iostream>
#include <SDL.h>

class CollisionEngine {
public:
    CollisionEngine(EntityManager& entityManager, Dispatcher& dispatcher) : entityManager(entityManager),
                                                                            dispatcher(dispatcher) {};
    void setBoundaryBox(int entityUID, float posX, float posY, float width, float height);
    void update();


private:
    EntityManager& entityManager;
    Dispatcher& dispatcher;
};



#endif //BLOOM_ENGINE_COLLISIONENGINE_H
