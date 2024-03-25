//
// Created by Jacob Ross on 3/24/24.
//

#ifndef BLOOM_ENGINE_INPUT_H
#define BLOOM_ENGINE_INPUT_H

#include <unordered_map>
#include <SDL.h>

class Input {
public:
    std::unordered_map<SDL_Keycode, std::array<float, 2>> keyBindings;


private:
};

#endif //BLOOM_ENGINE_INPUT_H
