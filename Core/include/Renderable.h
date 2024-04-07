//
// Created by Jacob Ross on 3/24/24.
//

#ifndef BLOOM_ENGINE_RENDERABLE_H
#define BLOOM_ENGINE_RENDERABLE_H

#include "Component.h"

#include <SDL.h>

enum class RenderLayer {
    background,
    character,
    foreground
};

class  Renderable : public  Component {
public:
    Renderable() {
        type = "Renderable";
         renderLayer = RenderLayer::background;
    }

    RenderLayer renderLayer;
};


#endif //BLOOM_ENGINE_RENDERABLE_H