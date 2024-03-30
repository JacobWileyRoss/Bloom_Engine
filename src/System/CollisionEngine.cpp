//
// Created by Jacob Ross on 3/25/24.
//

#include "../../include/System/CollisionEngine.h"

void CollisionEngine::update() {
    //std::cout << "CollisionEngine::update called successfully" << std::endl;
    auto entities = entityManager.getEntitiesWithComponent<Collider>(ComponentTypes::Collider);

    // Naive collision detection: Check every pair of entities for collision
    for (auto i = entities.begin(); i != entities.end(); ++i) {
        for (auto j = std::next(i); j != entities.end(); ++j) {
            //std::cout << "Entity i: " << *i << std::endl;
            //std::cout << "Entity j: " << *j << std::endl;
            auto& entityA = entityManager.getEntity(*i);
            auto& entityB = entityManager.getEntity(*j);

            //Assuming getEntityComponent takes the entity ID and component type name
            auto& colliderA = entityManager.getEntityComponent<Collider>(*i, ComponentTypes::Collider);
            auto& colliderB = entityManager.getEntityComponent<Collider>(*j, ComponentTypes::Collider);
            auto& physicsA = entityManager.getEntityComponent<Physics>(*i, ComponentTypes::Physics);
            auto& physicsB = entityManager.getEntityComponent<Physics>(*j, ComponentTypes::Physics);
            //std::cout << "Entity i rectX: " << colliderA.rect.x << " Entity i recty: " << colliderA.rect.y
            //        << " Entity i rectW: " << colliderA.rect.w << " Entity i rectH: " << colliderA.rect.h << std::endl;
            //std::cout << "Entity j rectX: " << colliderB.rect.x << " Entity j recty: " << colliderB.rect.y
            //          << " Entity j rectW: " << colliderB.rect.w << " Entity j rectH: " << colliderB.rect.h << std::endl;
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
    std::cout << "[DEBUG] CollisionEngine::setBoundaryBox() called successfully" << std::endl;
    collider.rect.x = posX;
    collider.rect.y = posY;
    collider.rect.w = width;
    collider.rect.h = height;
    std::cout << "rectX: " << collider.rect.x << " rectY: " << collider.rect.y << " rectW: " <<
                collider.rect.w << " rectH: " << collider.rect.h << std::endl;
}
