//
// Created by Jacob Ross on 3/24/24.
//

#ifndef BLOOM_ENGINE_RENDERABLE_H
#define BLOOM_ENGINE_RENDERABLE_H

#include "Component.h"

#include "../../../vendor/sdl2/2.30.1/include/SDL2/SDL.h"

enum class RenderLayer {
    background,
    character,
    foreground
};

inline std::string renderLayerToString(RenderLayer& layer) {
    switch (layer) {
        case RenderLayer::background: return "background";
        case RenderLayer::character: return "character";
        case RenderLayer::foreground: return "foreground";

    }
}

class  Renderable : public  Component {
public:
    Renderable() {
        type = "Renderable";
         renderLayer = RenderLayer::background;
    }

    RenderLayer renderLayer;
};


#endif //BLOOM_ENGINE_RENDERABLE_H
