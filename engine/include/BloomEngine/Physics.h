//
// Created by Jacob Ross on 3/24/24.
//

#ifndef BLOOM_ENGINE_PHYSICS_H
#define BLOOM_ENGINE_PHYSICS_H
#include "Component.h"

class Physics : public Component{
public:
    Physics() :  velX(0), velY(0), dirX(0), dirY(0), speed(100.0f) {}

    float velX;
    float velY;
    float dirX;
    float dirY;
    float speed;
};
#endif //BLOOM_ENGINE_PHYSICS_H
