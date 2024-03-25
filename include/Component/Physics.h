//
// Created by Jacob Ross on 3/24/24.
//

#ifndef BLOOM_ENGINE_PHYSICS_H
#define BLOOM_ENGINE_PHYSICS_H
#include "Component.h"

class Physics : public Component{
public:
    Physics() {
        type = "Physics";
        float velX = 0;
        float velY = 0;
        float dirX = 0; // Added for input direction
        float dirY = 0; // Added for input direction
        float speed = 100.0f; // You can now set speed per entity
    }
    float velX;
    float velY;
    float dirX;
    float dirY;
    float speed = 500;
};
#endif //BLOOM_ENGINE_PHYSICS_H
