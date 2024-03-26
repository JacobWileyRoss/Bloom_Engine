//
// Created by Jacob Ross on 3/24/24.
//

#include "../../include/System/PhysicsEngine.h"
#include "../../include/Component/Transform.h"
#include <iostream>

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

void PhysicsEngine::setTransform(int entityUID, float posX, float posY) {
    auto& transform = entityManager.getEntityComponent<Transform>
                                    (entityUID, ComponentTypes::Transform);

    transform.posX = posX;
    transform.posY = posY;
}
