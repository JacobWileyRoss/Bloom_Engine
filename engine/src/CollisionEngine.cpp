//
// Created by Jacob Ross on 3/25/24.
//

#include "BloomEngine/CollisionEngine.h"

void CollisionEngine::update() {
    //std::cout << "CollisionEngine::update called successfully" << std::endl;
    auto entities = entityManager.getEntitiesWithComponent<Collider>(ComponentTypes::Collider);

    // TODO Collision Detection needs a more efficient algorithm instead of checking every possible entity combination
    // Naive collision detection: Check every pair of entities for collision
    for (auto i = entities.begin(); i != entities.end(); ++i) {
        for (auto j = std::next(i); j != entities.end(); ++j) {
            // Unused debugging outputs
            //std::cout << "Entity i: " << *i << std::endl;
            //std::cout << "Entity j: " << *j << std::endl;
            auto& entityA = entityManager.getEntity(*i);
            auto& entityB = entityManager.getEntity(*j);

            // For entityA and entityB get each of their Collider and Physics components
            auto& colliderA = entityManager.getEntityComponent<Collider>
                    (*i, ComponentTypes::Collider);
            auto& colliderB = entityManager.getEntityComponent<Collider>
                    (*j, ComponentTypes::Collider);
            auto& physicsA = entityManager.getEntityComponent<Physics>
                    (*i, ComponentTypes::Physics);
            auto& physicsB = entityManager.getEntityComponent<Physics>
                    (*j, ComponentTypes::Physics);

            // Unused debugging outputs
            //std::cout << "Entity i rectX: " << colliderA.rect.x << " Entity i recty: " << colliderA.rect.y
            //        << " Entity i rectW: " << colliderA.rect.w << " Entity i rectH: " << colliderA.rect.h << std::endl;
            //std::cout << "Entity j rectX: " << colliderB.rect.x << " Entity j recty: " << colliderB.rect.y
            //          << " Entity j rectW: " << colliderB.rect.w << " Entity j rectH: " << colliderB.rect.h << std::endl;

            // Check entityA and entityB's Collider components SDL_rect for intersection. If HasIntersection is
            // ture, indicates collision between entityA and entityB
            if (SDL_HasIntersection(&colliderA.rect, &colliderB.rect)) {
                std::cout << "[INFO] Collision detected between Entity " << entityA.UID << " and Entity "
                << entityB.UID << std::endl;
                // Dispatches Collision Event to the registered functions in Core::Initialize()
                CollisionData collisionData(entityA.UID, entityB.UID, physicsA.velX,
                                            physicsA.velY,physicsB.velX, physicsB.velY);
                Event collisionEvent(EventType::Collision, collisionData);
                dispatcher.dispatchEvent(collisionEvent);
            }
        }
    }
}

// This function is for defining the SDL_rect size in a Collider component attached to an entity for collision detection
void CollisionEngine::setBoundaryBox(int entityUID, float posX, float posY, float width, float height) {
    auto& collider = entityManager.getEntityComponent<Collider>
            (entityUID, ComponentTypes::Collider);
    std::cout << "[DEBUG] CollisionEngine::setBoundaryBox() called successfully" << std::endl;
    collider.rect.x = posX;
    collider.rect.y = posY;
    collider.rect.w = width;
    collider.rect.h = height;
    std::cout << "rectX: " << collider.rect.x << " rectY: " << collider.rect.y << " rectW: " <<
                collider.rect.w << " rectH: " << collider.rect.h << std::endl;
}
