//
// Created by Jacob Ross on 3/24/24.
//

#ifndef BLOOM_ENGINE_PHYSICSENGINE_H
#define BLOOM_ENGINE_PHYSICSENGINE_H

#include "Dispatcher.h"
#include "Entity.h"
#include "Physics.h"
#include "Collider.h"


class PhysicsEngine {
public:
    explicit PhysicsEngine(EntityManager& entityManager, Dispatcher& dispatcher, float& deltaTime) :
                            entityManager(entityManager), dispatcher(dispatcher), deltaTime(deltaTime)
                            {std::cout <<"[INFO] Physics engine initialized successfully" << std::endl;};

    void update(float deltaTime);
    void handleInputEvent(const Event& event);
    void handleCollisionEvent(const Event& event);
    void applyForce(Entity& entity, float x, float y);
    void setTransform(int entityUID, float posX, float posY);

private:
    Dispatcher& dispatcher;
    EntityManager& entityManager;
    float& deltaTime;
};



#endif //BLOOM_ENGINE_PHYSICSENGINE_H
