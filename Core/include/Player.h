//
// Created by Jacob Ross on 3/24/24.
//

#ifndef BLOOM_ENGINE_PLAYER_H
#define BLOOM_ENGINE_PLAYER_H
#include "Component.h"

class Player : public Component {
public:
    Player() {
        type = "Player";
    }

    std::string getType() {
        return type;
    }

};
#endif //BLOOM_ENGINE_PLAYER_H
