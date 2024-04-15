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
    explicit PhysicsEngine( EntityManager& entityManager, Dispatcher& dispatcher,
                           float& deltaTime) : entityManager(entityManager),
                            dispatcher(dispatcher), deltaTime(deltaTime)
                            {std::cout <<"[INFO] Physics Engine initialized successfully" << std::endl;};

    void update(float deltaTime);
    void updateTopDownPhysics(int entityUID, float deltaTime);
    void updateSideScrollPhysics(int entityUID, float deltaTime);
    void handleInputEvent(const Event& event);
    void handleCollisionEvent(const Event& event);
    void applyForce(int entityUID, float x, float y);
    void setPhysics(int entityUID, float dirX, float dirY, float speed, PhysicsMode mode);
    void setPhysics(int entityUID, float dirX, float dirY, float speed, PhysicsMode mode, float gravity, float mass);
    void setPhysicsMode(int entityUID, PhysicsMode mode);
    void setIsJumping(int entityUID, bool isJumping);
    void setTransform(int entityUID, float posX, float posY);


private:
    Dispatcher& dispatcher;
    EntityManager& entityManager;
    float& deltaTime;
    float speedMultipler;
};



#endif //BLOOM_ENGINE_PHYSICSENGINE_H
