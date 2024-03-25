//
// Created by Jacob Ross on 3/24/24.
//

#ifndef BLOOM_ENGINE_RENDERABLE_H
#define BLOOM_ENGINE_RENDERABLE_H

#include "Component.h"

#include <SDL.h>

class  Renderable : public  Component {
public:
    Renderable() {
        type = "Renderable";
    }

};


#endif //BLOOM_ENGINE_RENDERABLE_H
