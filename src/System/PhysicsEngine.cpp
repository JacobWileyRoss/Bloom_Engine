//
// Created by Jacob Ross on 3/24/24.
//

#include "../../include/System/PhysicsEngine.h"
#include "../../include/Component/Transform.h"
#include <iostream>

// TODO I need to review the update() function and make sure I completely understand it and determine if its the best method
void PhysicsEngine::update(float deltaTime) {
    for (auto& [entityUID, entity] : entityManager.entities) {
        if (entityManager.hasComponent(entityUID, ComponentTypes::Physics)) {
            Physics& physics = entityManager.getEntityComponent<Physics>
                    (entityUID, ComponentTypes::Physics);

            // Directly apply movement based on direction and speed
            auto& transform = entityManager.getEntityComponent<Transform>
                    (entityUID, ComponentTypes::Transform);
            transform.posX += physics.dirX * physics.speed * deltaTime;
            transform.posY += physics.dirY * physics.speed * deltaTime;

            // Check if the entity has a Collider component and update its position
            if (entityManager.hasComponent(entityUID, ComponentTypes::Collider)) {
                auto& collider = entityManager.getEntityComponent<Collider>
                        (entityUID, ComponentTypes::Collider);
                collider.rect.x = transform.posX; // Ensure proper type casting
                collider.rect.y = transform.posY;
            }
        }
    }
}

// TODO this needs to be updated to support Input controls being defined in Lua and not hardcoded by InputProcessor
// Handling of input event created by the InputProcessor and sent to the Dispatcher.
void PhysicsEngine::handleInputEvent(const Event& event) {
    int entityUID = event.entityUID;

    // Check if the entity exists before attempting to access it
    if (entityManager.entities.find(entityUID) == entityManager.entities.end()) {
        std::cerr << "[ERROR] PhysicsEngine::handleInputEvent - Entity with UID " <<
                        entityUID << " not found." << std::endl;
        return;
    }

    Entity& entity = entityManager.getEntity(entityUID);

    // Ensure the entity has a Physics component before proceeding
    if (entity.components.find(ComponentTypes::Physics) == entity.components.end()) {
        std::cerr << "[ERROR] PhysicsEngine::handleInputEvent - No Physics component found for Entity UID "
                    << entityUID << "." << std::endl;
        return;
    }

    auto& physics = entityManager.getEntityComponent<Physics>
            (entityUID, ComponentTypes::Physics);

    float velX = physics.velX * physics.speed;
    float velY = physics.velY * physics.speed;

    std::cout << "[DEBUG] PhysicsEngine::handleInputEvent - Processing input for Entity UID " << entityUID
              << ". Velocity X: " << velX << ", Velocity Y: " << velY << std::endl;

    applyForce(entity, velX, velY);
}

// TODO I need to review the handleCollisionEvent and make sure I completely understand it and determine if it is the best method
// Takes 2 colliding entities and determines if any of them are the player object, the player entity gets velocity set
// to 0 and transform set back. Checking for player because if that logic is applied to other entities, the player can
// can push them back by bumping into them even if that entity was stationary
void PhysicsEngine::handleCollisionEvent(const Event &event) {
    auto collisionData = std::get<CollisionData>(event.eventData);
    bool isEntityAPlayer = entityManager.hasComponent(collisionData.entity1UID, ComponentTypes::Player);
    bool isEntityBPlayer = entityManager.hasComponent(collisionData.entity2UID, ComponentTypes::Player);
    auto& spriteA = entityManager.getEntityComponent<Sprite>(collisionData.entity1UID, ComponentTypes::Sprite);
    auto& spriteB = entityManager.getEntityComponent<Sprite>(collisionData.entity2UID, ComponentTypes::Sprite);
    auto& physicsA = entityManager.getEntityComponent<Physics>(collisionData.entity1UID, ComponentTypes::Physics);
    auto& physicsB = entityManager.getEntityComponent<Physics>(collisionData.entity2UID, ComponentTypes::Physics);
    auto& transformA = entityManager.getEntityComponent<Transform>(collisionData.entity1UID, ComponentTypes::Transform);
    auto& transformB = entityManager.getEntityComponent<Transform>(collisionData.entity2UID, ComponentTypes::Transform);

    // Calculate penetration depth and resolve collision based on it
    float penetrationDepthX = std::min(transformA.posX + spriteA.rect.w - transformB.posX, transformB.posX + spriteB.rect.w - transformA.posX);
    float penetrationDepthY = std::min(transformA.posY + spriteA.rect.h - transformB.posY, transformB.posY + spriteB.rect.h - transformA.posY);

    // Determine the direction to push entities away based on the least penetration depth
    if (isEntityAPlayer) {
        // Move player entity A back slightly
        if (penetrationDepthX < penetrationDepthY) {
            physicsA.velX = 0; // Stop horizontal movement
            if (transformA.posX < transformB.posX) {
                transformA.posX -= 5; // Move back left
            } else {
                transformA.posX += 5; // Move back right
            }
        } else {
            physicsA.velY = 0; // Stop vertical movement
            if (transformA.posY < transformB.posY) {
                transformA.posY -= 5; // Move back up
            } else {
                transformA.posY += 5; // Move back down
            }
        }
    } else if (isEntityBPlayer) {
        // Move player entity B back slightly
        if (penetrationDepthX < penetrationDepthY) {
            physicsB.velX = 0; // Stop horizontal movement
            if (transformB.posX < transformA.posX) {
                transformB.posX -= 5; // Move back left
            } else {
                transformB.posX += 5; // Move back right
            }
        } else {
            physicsB.velY = 0; // Stop vertical movement
            if (transformB.posY < transformA.posY) {
                transformB.posY -= 5; // Move back up
            } else {
                transformB.posY += 5; // Move back down
            }
        }
    }
    std::cout << "[INFO] PhysicsEngine::handleCollisionEvent - Collision resolved for entities " << collisionData.entity1UID << " and " << collisionData.entity2UID << std::endl;
}

// Applies force to Entity by modifying the transform component by the vel * delta time
void PhysicsEngine::applyForce(Entity& entity, float velX, float velY) {
    // Ensure the entity has a Transform component before proceeding
    if (entity.components.find(ComponentTypes::Transform) == entity.components.end()) {
        std::cerr << "[ERROR] PhysicsEngine::applyForce - No Transform component found for Entity UID "
                        << entity.UID << "." << std::endl;
        return;
    }

    auto& transform = entityManager.getEntityComponent<Transform>
            (entity.UID, ComponentTypes::Transform);
    transform.posX += velX * deltaTime;
    transform.posY += velY * deltaTime;

    std::cout << "[INFO] PhysicsEngine::applyForce - Entity UID " << entity.UID << " new position: X: "
                << transform.posX << ", Y: " << transform.posY << std::endl;
}

// This function can set a Transform Component's X and Y coordinate position to the specified coordinates
void PhysicsEngine::setTransform(int entityUID, float posX, float posY) {
    auto& transform = entityManager.getEntityComponent<Transform>
                                    (entityUID, ComponentTypes::Transform);
    transform.posX = posX;
    transform.posY = posY;
    std::cout << "[INFO] setTransform() called for entityUID: " << entityUID << std::endl;
}
