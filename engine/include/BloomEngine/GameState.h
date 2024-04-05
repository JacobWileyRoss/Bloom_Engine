//
// Created by Jacob Ross on 3/29/24.
//

#ifndef BLOOM_ENGINE_GAMESTATE_H
#define BLOOM_ENGINE_GAMESTATE_H

#include <unordered_set>
#include "EntityManager.h"

class GameState {
public:
    GameState(EntityManager& entityManager) : entityManager(entityManager){};
    virtual void enter() = 0; // Called when entering the state
    virtual void exit() = 0;  // Called when exiting the state
    virtual void update(float deltaTime) = 0; // Update the state logic
    virtual void render() = 0; // Render the state visuals


    virtual ~GameState() = default;

private:
    EntityManager& entityManager;

};

#endif //BLOOM_ENGINE_GAMESTATE_H
