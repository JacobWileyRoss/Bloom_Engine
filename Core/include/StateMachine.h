//
// Created by Jacob Ross on 3/29/24.
//

#ifndef BLOOM_ENGINE_STATEMACHINE_H
#define BLOOM_ENGINE_STATEMACHINE_H

#include <stack>
#include <sol/sol.hpp>
#include "GameState.h"
#include "LuaGameState.h"


class StateMachine {
private:
    std::stack<GameState*> states;
    EntityManager& entityManager;
    sol::state& lua; // Reference to the Lua state


public:
    StateMachine(EntityManager& entityManager, sol::state& lua) : entityManager(entityManager), lua(lua) {}

    void changeState(const std::string& stateName);
    void pushState(GameState* state);
    void popState();
    void update(float deltaTime);
    void render();
};


#endif //BLOOM_ENGINE_STATEMACHINE_H
