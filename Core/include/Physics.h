//
// Created by Jacob Ross on 3/24/24.
//

#ifndef BLOOM_ENGINE_PHYSICS_H
#define BLOOM_ENGINE_PHYSICS_H
#include "Component.h"

enum class PhysicsMode {
    TopDown,
    SideScroll
};

inline std::string physicsModeToString(PhysicsMode& mode) {
    switch (mode) {
        case PhysicsMode::TopDown: return "TopDown";
        case PhysicsMode::SideScroll: return "SideScroll";

    }
}

class Physics : public Component{
public:
    Physics() {
        type = "Physics";
        mode = PhysicsMode::SideScroll;
        float velX = 0;
        float velY = 0;
        float dirX = 0;
        float dirY = 0;
        float speed = 100.0f;
    }
    PhysicsMode mode;
    bool applyGravity;
    float velX;
    float velY;
    float dirX;
    float dirY;
    float mass = 0;
    float speed = 250;
    float gravity = 0;
    bool isJumping = false;
    float jumpForce = 300.0;


};
#endif //BLOOM_ENGINE_PHYSICS_H
