//
// Created by Jacob Ross on 3/24/24.
//

#ifndef BLOOM_ENGINE_SPRITE_H
#define BLOOM_ENGINE_SPRITE_H

#include <SDL.h>


class Sprite : public Component {
public:
    Sprite() {
        type = "Sprite";
        rect.x = 0;
        rect.y = 0;
        rect.w = 32;
        rect.h = 32;
    }

    // SDL_FRect for floating point positioning
    SDL_FRect rect;

};


#endif //BLOOM_ENGINE_SPRITE_H
