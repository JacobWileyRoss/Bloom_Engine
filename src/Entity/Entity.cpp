//
// Created by Jacob Ross on 3/24/24.
//

#include "../../include/Entity/Entity.h"

Entity::Entity(int newUID) {
    UID = newUID;
    std::cout << "Entity: " << newUID << " created!" << std::endl;
}