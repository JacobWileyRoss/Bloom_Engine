//
// Created by Jacob Ross on 3/24/24.
//

#ifndef BLOOM_ENGINE_TRANSFORM_H
#define BLOOM_ENGINE_TRANSFORM_H
#include "Component.h"

class Transform : public Component {

public:
    Transform() {
        type = "Transform";
        posX = {};
        posY = {};
    }
    float posX;
    float posY;
private:

};
#endif //BLOOM_ENGINE_TRANSFORM_H
