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
        float dirX = 0;
        float dirY = 0;
        float speed = 100.0f;
    }
    float velX;
    float velY;
    float dirX;
    float dirY;
    // TODO needs to be scriptable by Lua via ScriptingEngine
    float speed = 250;
};
#endif //BLOOM_ENGINE_PHYSICS_H
