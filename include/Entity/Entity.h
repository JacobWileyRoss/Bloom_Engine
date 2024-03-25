//
// Created by Jacob Ross on 3/24/24.
//

#ifndef BLOOM_ENGINE_ENTITY_H
#define BLOOM_ENGINE_ENTITY_H


#include <memory>
#include <unordered_map>
#include "../Component/Component.h"
#include "../Component/ComponentTypes.h"



class Entity {
public:
    Entity(int newUID) {
        UID = newUID;
    }
    int UID;
    std::unordered_map<ComponentTypes, std::shared_ptr<Component> > components;
};
#endif //BLOOM_ENGINE_ENTITY_H
