//
// Created by Jacob Ross on 3/25/24.
//

#ifndef BLOOM_ENGINE_COLLISIONENGINE_H
#define BLOOM_ENGINE_COLLISIONENGINE_H

#include "EntityManager.h"
#include "../Component/Collider.h"
#include <iostream>
#include <SDL.h>

class CollisionEngine {
public:
//    void update(EntityManager& entityManager) {
//        Collider colliderType(0,0,32,32);
//        auto entities = entityManager.getEntitiesWithComponent<Collider>(colliderType);
//
//        // Naive collision detection: Check every pair of entities for collision
//        for (auto i = entities.begin(); i != entities.end(); ++i) {
//            for (auto j = std::next(i); j != entities.end(); ++j) {
//                Entity& entityA = entityManager.getEntity(*i);
//                Entity& entityB = entityManager.getEntity(*j);
//
//                // Assuming getEntityComponent takes the entity ID and component type name
//                //Collider& colliderA = entityManager.getEntityComponent<Collider>(entityA, "Collider");
//                //Collider& colliderB = entityManager.getEntityComponent<Collider>(entityB, "Collider");
//
//                if (SDL_HasIntersection(&colliderA.rect, &colliderB.rect)) {
//                    std::cout << "Collision detected between Entity " << entityA.UID << " and Entity " << entityB.UID << std::endl;
//                    // Handle collision (e.g., stop movement, adjust positions, etc.)
//                }
//            }
//        }
//    }
};


#endif //BLOOM_ENGINE_COLLISIONENGINE_H
