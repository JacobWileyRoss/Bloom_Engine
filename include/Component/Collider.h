//
// Created by Jacob Ross on 3/25/24.
//

#ifndef BLOOM_ENGINE_COLLIDER_H
#define BLOOM_ENGINE_COLLIDER_H

// Collider.h
#pragma once
#include <SDL.h>
#include "Component.h"

class Collider : public Component {
public:
    SDL_Rect rect;

    Collider() {
        type = "Collider";
        int x = {};
        int y = {};
        int w = {};
        int h = {};
    }

    Collider(int x, int y, int width, int height) {
        rect = {x, y, width, height};
    }
};


#endif //BLOOM_ENGINE_COLLIDER_H
