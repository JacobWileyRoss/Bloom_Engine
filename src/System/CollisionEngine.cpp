//
// Created by Jacob Ross on 3/25/24.
//

#include "../../include/System/CollisionEngine.h"

void CollisionEngine::update() {
    auto entities = entityManager.getEntitiesWithComponent<Collider>(ComponentTypes::Collider);

    // Naive collision detection: Check every pair of entities for collision
    for (auto i = entities.begin(); i != entities.end(); ++i) {
        for (auto j = std::next(i); j != entities.end(); ++j) {
            auto& entityA = entityManager.getEntity(*i);
            auto& entityB = entityManager.getEntity(*j);

            //Assuming getEntityComponent takes the entity ID and component type name
            auto& colliderA = entityManager.getEntityComponent<Collider>(*i, ComponentTypes::Collider);
            auto& colliderB = entityManager.getEntityComponent<Collider>(*j, ComponentTypes::Collider);
            auto& physicsA = entityManager.getEntityComponent<Physics>(*i, ComponentTypes::Physics);
            auto& physicsB = entityManager.getEntityComponent<Physics>(*j, ComponentTypes::Physics);

            if (SDL_HasIntersection(&colliderA.rect, &colliderB.rect)) {
                std::cout << "Collision detected between Entity " << entityA.UID << " and Entity " << entityB.UID << std::endl;
                // Handle collision (e.g., stop movement, adjust positions, etc.)/* Velocities etc. */};
                CollisionData collisionData(entityA.UID, entityB.UID, physicsA.velX, physicsA.velY,
                                                          physicsB.velX, physicsB.velY);
                Event collisionEvent(EventType::Collision, collisionData);
                dispatcher.dispatchEvent(collisionEvent);
            }
        }
    }
}

void CollisionEngine::setBoundaryBox(int entityUID, float posX, float posY, float width, float height) {
    auto& collider = entityManager.getEntityComponent<Collider>(entityUID, ComponentTypes::Collider);
    collider.rect.x = posX;
    collider.rect.y = posY;
    collider.rect.w = width;
    collider.rect.h = height;
}
