//
// Created by Jacob Ross on 3/29/24.
//

#ifndef BLOOM_ENGINE_STATEMACHINE_H
#define BLOOM_ENGINE_STATEMACHINE_H

#include <stack>
#include <sol/sol.hpp>
#include "../../include/GameState/GameState.h"
#include "../../include/GameState/LuaGameState.h"


class StateMachine {
private:
    std::stack<GameState*> states;
    EntityManager& entityManager;
    sol::state& lua; // Reference to the Lua state


public:
    StateMachine(EntityManager& entityManager, sol::state& lua) : entityManager(entityManager), lua(lua) {}

    void changeState(const std::string& stateName) {
        if (!states.empty()) {
            states.top()->exit();
            delete states.top();
            states.pop();
        }

        // Use the Lua state registry or another mechanism to find the Lua table
        LuaGameState* newState = new LuaGameState(entityManager, lua, stateName);
        states.push(newState);
        states.top()->enter();
    }

    void pushState(GameState* state) {
        if (!states.empty()) {
            states.top()->exit();
        }

        states.push(state);
        states.top()->enter();
    }

    void popState() {
        if (!states.empty()) {
            states.top()->exit();
            delete states.top();
            states.pop();
        }

        if (!states.empty()) {
            states.top()->enter();
        }
    }

    void update(float deltaTime) {
        if (!states.empty()) {
            states.top()->update(deltaTime);
        }
    }

    void render() {
        if (!states.empty()) {
            states.top()->render();
        }
    }
};


#endif //BLOOM_ENGINE_STATEMACHINE_H
