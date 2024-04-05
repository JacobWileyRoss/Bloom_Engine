//
// Created by Jacob Ross on 3/29/24.
//

#include "BloomEngine/StateMachine.h"


// TODO review state machine, GameState and LuaGameState and how they interact and make sure it's the best method

void StateMachine::changeState(const std::string& stateName) {
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

void StateMachine::pushState(GameState *state) {
    if (!states.empty()) {
        states.top()->exit();
    }

    states.push(state);
    states.top()->enter();
}

void StateMachine::popState() {
    if (!states.empty()) {
        states.top()->exit();
        delete states.top();
        states.pop();
    }

    if (!states.empty()) {
        states.top()->enter();
    }
}

void StateMachine::update(float deltaTime) {
    if (!states.empty()) {
        states.top()->update(deltaTime);
    }
}

void StateMachine::render() {
    if (!states.empty()) {
        states.top()->render();
    }
}