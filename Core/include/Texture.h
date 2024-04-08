//
// Created by Jacob Ross on 3/24/24.
//

#ifndef BLOOM_ENGINE_TEXTURE_H
#define BLOOM_ENGINE_TEXTURE_H
#include <SDL.h>
#include <SDL_image.h>

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
