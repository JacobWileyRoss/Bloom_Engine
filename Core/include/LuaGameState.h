//
// Created by Jacob Ross on 3/29/24.
//

#ifndef BLOOM_ENGINE_LUAGAMESTATE_H
#define BLOOM_ENGINE_LUAGAMESTATE_H

#include "GameState.h"
#include <sol/sol.hpp>

class LuaGameState : public GameState {
protected:
    sol::state& lua;
    std::string stateName;
    EntityManager& entityManager;


public:
    LuaGameState(EntityManager& entityManager, sol::state& lua, const std::string& stateName)
            : GameState(entityManager), entityManager(entityManager), lua(lua), stateName(stateName) {}


    void enter() override {
        lua[stateName]["enter"]();
    }

    void exit() override {
        lua[stateName]["exit"]();
    }

    void update(float deltaTime) override {
        lua[stateName]["update"](deltaTime);
    }

    void render() override {
        lua[stateName]["render"]();
    }

    std::string serialize() override {

    }

};

#endif //BLOOM_ENGINE_LUAGAMESTATE_H
