//
// Created by Jacob Ross on 3/24/24.
//

#include "../include/PhysicsEngine.h"
#include "../include/Transform.h"
#include <iostream>

// Gets all entities with a Physics component and updates their position accordingly
void PhysicsEngine::update(float deltaTime) {
    for (auto& [entityUID, entity] : entityManager.entities) {
        if (entityManager.hasComponent(entityUID, ComponentType::Physics)) {

            // Get the entity's Physics component
            Physics& physics = entityManager.getEntityComponent<Physics>
                    (entityUID, ComponentType::Physics);

            // Get the entity's Transform component
            auto& transform = entityManager.getEntityComponent<Transform>
                    (entityUID, ComponentType::Transform);

            // Adjust the X and Y position according to direction, speed, and deltaTime
            transform.posX += physics.dirX * physics.speed * deltaTime;
            transform.posY += physics.dirY * physics.speed * deltaTime;

            // Check if the entity has a Collider component, if true updates Collider rect position used for
            // collision detection
            if (entityManager.hasComponent(entityUID, ComponentType::Collider)) {
                auto& collider = entityManager.getEntityComponent<Collider>
                        (entityUID, ComponentType::Collider);
                collider.rect.x = transform.posX;
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
    if (entity.components.find(ComponentType::Physics) == entity.components.end()) {
        std::cerr << "[ERROR] PhysicsEngine::handleInputEvent - No Physics component found for Entity UID "
                    << entityUID << "." << std::endl;
        return;
    }

    auto& physics = entityManager.getEntityComponent<Physics>
            (entityUID, ComponentType::Physics);

    float velX = physics.velX * physics.speed;
    float velY = physics.velY * physics.speed;

    std::cout << "[DEBUG] PhysicsEngine::handleInputEvent - Processing input for Entity UID " << entityUID
              << ". Velocity X: " << velX << ", Velocity Y: " << velY << std::endl;

    applyForce(entityUID, velX, velY);
}

// TODO I need to review the handleCollisionEvent and make sure I completely understand it and determine if it is the best method
// Takes 2 colliding entities and determines if any of them are the player object, the player entity gets velocity set
// to 0 and transform set back. Checking for player because if that logic is applied to other entities, the player can
// can push them back by bumping into them even if that entity was stationary
void PhysicsEngine::handleCollisionEvent(const Event &event) {
    auto collisionData = std::get<CollisionData>(event.eventData);
    bool isEntityAPlayer = entityManager.hasComponent(collisionData.entity1UID, ComponentType::Player);
    bool isEntityBPlayer = entityManager.hasComponent(collisionData.entity2UID, ComponentType::Player);
    auto& spriteA = entityManager.getEntityComponent<Sprite>(collisionData.entity1UID, ComponentType::Sprite);
    auto& spriteB = entityManager.getEntityComponent<Sprite>(collisionData.entity2UID, ComponentType::Sprite);
    auto& physicsA = entityManager.getEntityComponent<Physics>(collisionData.entity1UID, ComponentType::Physics);
    auto& physicsB = entityManager.getEntityComponent<Physics>(collisionData.entity2UID, ComponentType::Physics);
    auto& transformA = entityManager.getEntityComponent<Transform>(collisionData.entity1UID, ComponentType::Transform);
    auto& transformB = entityManager.getEntityComponent<Transform>(collisionData.entity2UID, ComponentType::Transform);

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
void PhysicsEngine::applyForce(int entityUID, float dirX, float dirY) {
    auto& physics = entityManager.getEntityComponent<Physics>(entityUID, ComponentType::Physics);
    // Normalize the direction vector
    float magnitude = std::hypot(dirX, dirY);
    if (magnitude > 0) {
        dirX /= magnitude;
        dirY /= magnitude;
    }

    // Calculate velocity based on direction and player speed
    float velX = dirX * physics.speed * deltaTime;
    float velY = dirY * physics.speed * deltaTime;

    // Apply the calculated velocity to the entity's transform component
    auto& entity = entityManager.getEntity(entityUID);
    if (entity.components.find(ComponentType::Transform) != entity.components.end()) {
        auto& transform = entityManager.getEntityComponent<Transform>(entity.UID, ComponentType::Transform);
        transform.posX += velX;
        transform.posY += velY;
        std::cout << "[INFO] PhysicsEngine::applyForce - Moved Entity UID " << entity.UID
                  << " to new position: X: " << transform.posX << ", Y: " << transform.posY << std::endl;
    } else {
        std::cerr << "[ERROR] PhysicsEngine::applyForce - No Transform component found for Entity UID "
                  << entity.UID << "." << std::endl;
    }
}

void PhysicsEngine::setPhysics(int entityUID, float dirX, float dirY, float speed){
    auto& physics = entityManager.getEntityComponent<Physics>
                                (entityUID, ComponentType::Physics);
    physics.dirX = dirX;
    physics.dirY = dirY;
    physics.speed = speed;
    std::cout << "[INFO] setPhysics() called for entityUID: " << entityUID << std::endl;
}


// This function can set a Transform Component's X and Y coordinate position to the specified coordinates
void PhysicsEngine::setTransform(int entityUID, float posX, float posY) {
    auto& transform = entityManager.getEntityComponent<Transform>
                                    (entityUID, ComponentType::Transform);
    transform.posX = posX;
    transform.posY = posY;
    std::cout << "[INFO] setTransform() called for entityUID: " << entityUID << std::endl;
}
