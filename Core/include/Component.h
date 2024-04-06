//
// Created by Jacob Ross on 3/24/24.
//

#ifndef BLOOM_ENGINE_COMPONENT_H
#define BLOOM_ENGINE_COMPONENT_H

#include <iostream>


class Component {
public:
    std::string type;
    virtual ~Component() = default;

};


#endif //BLOOM_ENGINE_COMPONENT_H
