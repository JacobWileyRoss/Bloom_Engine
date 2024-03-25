//
// Created by Jacob Ross on 3/24/24.
//

#ifndef BLOOM_ENGINE_PHYSICSENGINE_H
#define BLOOM_ENGINE_PHYSICSENGINE_H

#include "Dispatcher.h"
#include "../Entity/Entity.h"
#include "../Component/Physics.h"
#include "../Component/Collider.h"


class PhysicsEngine {
public:
    explicit PhysicsEngine(EntityManager& entityManager, Dispatcher& dispatcher, float& deltaTime) :
                            entityManager(entityManager), dispatcher(dispatcher), deltaTime(deltaTime)
                            {std::cout <<"[INFO] Physics Engine initialized successfully" << std::endl;};

    void update(float deltaTime);
    void handleInputEvent(const Event& event);
    void applyForce(Entity& entity, float x, float y);

private:
    Dispatcher& dispatcher;
    EntityManager& entityManager;
    float& deltaTime;
    float speedMultipler;
};



#endif //BLOOM_ENGINE_PHYSICSENGINE_H
