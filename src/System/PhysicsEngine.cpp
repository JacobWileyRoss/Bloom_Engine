//
// Created by Jacob Ross on 3/24/24.
//

#include "../../include/System/PhysicsEngine.h"
#include "../../include/Component/Transform.h"
#include <iostream>

void PhysicsEngine::update(float deltaTime) {
    for (auto& [entityUID, entity] : entityManager.entities) {
        if (entityManager.hasComponent(entityUID, "Physics")) {
            Physics& physics = entityManager.getEntityComponent<Physics>(entity, "Physics");

            // Directly apply movement based on direction and speed
            auto& transform = entityManager.getEntityComponent<Transform>(entity, "Transform");
            transform.posX += physics.dirX * physics.speed * deltaTime;
            transform.posY += physics.dirY * physics.speed * deltaTime;
        }
    }
}

void PhysicsEngine::handleInputEvent(const Event& event) {
    int entityUID = event.entityUID;

    // Check if the entity exists before attempting to access it
    if (entityManager.entities.find(entityUID) == entityManager.entities.end()) {
        std::cerr << "[ERROR] PhysicsEngine::handleInputEvent - Entity with UID " << entityUID << " not found." << std::endl;
        return;
    }

    Entity& entity = entityManager.getEntity(entityUID);

    // Ensure the entity has a Physics component before proceeding
    if (entity.components.find("Physics") == entity.components.end()) {
        std::cerr << "[ERROR] PhysicsEngine::handleInputEvent - No Physics component found for Entity UID " << entityUID << "." << std::endl;
        return;
    }

    auto& physics = entityManager.getEntityComponent<Physics>(entity, "Physics");

    float velX = physics.velX * physics.speed;
    float velY = physics.velY * physics.speed;

    std::cout << "[DEBUG] PhysicsEngine::handleInputEvent - Processing input for Entity UID " << entityUID
              << ". Velocity X: " << velX << ", Velocity Y: " << velY << std::endl;

    applyForce(entity, velX, velY);
}

void PhysicsEngine::applyForce(Entity& entity, float velX, float velY) {
    // Ensure the entity has a Transform component before proceeding
    if (entity.components.find("Transform") == entity.components.end()) {
        std::cerr << "[ERROR] PhysicsEngine::applyForce - No Transform component found for Entity UID " << entity.UID << "." << std::endl;
        return;
    }

    auto& transform = entityManager.getEntityComponent<Transform>(entity, "Transform");
    transform.posX += velX * deltaTime;
    transform.posY += velY * deltaTime;

    std::cout << "[INFO] PhysicsEngine::applyForce - Entity UID " << entity.UID << " new position: X: " << transform.posX << ", Y: " << transform.posY << std::endl;
}
