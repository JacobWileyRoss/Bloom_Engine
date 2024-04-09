//
// Created by Jacob Ross on 3/24/24.
//

#ifndef BLOOM_ENGINE_TEXTURE_H
#define BLOOM_ENGINE_TEXTURE_H

#include "../../../vendor/sdl2/2.30.1/include/SDL2/SDL.h"
#include "../../../vendor/sdl2_image/2.8.2_1/include/SDL2/SDL_image.h"

class Texture : public Component {
public:
    Texture() {
        type = "Texture";
    }

    SDL_Texture* texture;
    std::string filepath;
    int width;
    int height;
};
#endif //BLOOM_ENGINE_TEXTURE_H
