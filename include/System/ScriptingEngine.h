//
// Created by Jacob Ross on 3/28/24.
//

#ifndef BLOOM_ENGINE_SCRIPTINGENGINE_H
#define BLOOM_ENGINE_SCRIPTINGENGINE_H

#include <sol/sol.hpp>
#include "EntityManager.h"
#include "PhysicsEngine.h"
#include "RenderingEngine.h"
#include "AnimationEngine.h"
#include "CollisionEngine.h"
#include "../../include/Component/Animation.h"

class ScriptingEngine {
public:
    explicit ScriptingEngine(EntityManager& entityManager, Dispatcher& dispatcher, RenderingEngine& renderingEngine,
                             AnimationEngine& animationEngine,
                             PhysicsEngine& physicsEngine) :
                             entityManager(entityManager),
                             dispatcher(dispatcher),
                             renderingEngine(renderingEngine),
                             animationEngine(animationEngine),
                             physicsEngine(physicsEngine){
        lua.open_libraries(sol::lib::base, sol::lib::math, sol::lib::table);
        bindToLua();
    }

    void initialize() {
        lua["initialize"]();
    }

    sol::state& getLuaState() {
        return lua;
    }

    void update(float deltaTime) {
        // Example: Call the "update" function defined in Lua, passing deltaTime
        lua["update"](deltaTime);
    }

    void loadScript(const std::string& scriptPath) {
        lua.script_file(scriptPath);
    }


    void bindToLua() {
        /* Essential System's functionality exposed to Lua */

        // Expose the ComponentTypes to Lua
        lua["ComponentTypes"] = lua.create_table_with(
                "Animation", ComponentTypes::Animation,
                "Collider", ComponentTypes::Collider,
                "Event", ComponentTypes::Event,
                "Physics", ComponentTypes::Physics,
                "Player", ComponentTypes::Player,
                "Renderable", ComponentTypes::Renderable,
                "Sprite", ComponentTypes::Sprite,
                "Texture", ComponentTypes::Texture,
                "Transform", ComponentTypes::Transform
        );

        // Expose the AnimationTypes to Lua
        lua["AnimationTypes"] = lua.create_table_with(
                "WalkCycleUp", AnimationType::WalkCycleUP,
                "WalkCycleDown", AnimationType::WalkCycleDOWN,
                "WalkCycleLeft", AnimationType::WalkCycleLEFT,
                "WalkCycleRight", AnimationType::WalkCycleRIGHT
        );

        // Expose the RenderLayer types to Lua
        lua["RenderLayer"] = lua.create_table_with(
                "background", RenderLayer::background,
                "character", RenderLayer::character,
                "foreground", RenderLayer::foreground
                // Add other layers as needed
        );

        // Expose game functions, entities, and components to Lua
        // Exposing a function to log messages from Lua:
        lua.set_function("logMessage", [](const std::string& message) {
            std::cout << message << std::endl;
        });

        // Exposing EntityManager's createEntity() functionality
        lua.set_function("createEntity", [this]() {
          int newEntity = entityManager.createEntity();
            return newEntity;

        });

        lua.set_function("attachComponent", [this](int entityUID, ComponentTypes componentType) {
            entityManager.attachComponent(entityUID, componentType);
        });

        lua.set_function("setSprite", [this](int entityUID, float x, float y, float w, float h) {
            renderingEngine.setSprite(entityUID, x, y, w, h);
        });

        lua.set_function("setTexture", [this](int entityUID, const char* filename) {
            renderingEngine.setTexture(entityUID, filename);
        });

        lua.set_function("setRenderLayer", [this](int entityUID, RenderLayer layer) {
           renderingEngine.setRenderLayer(entityUID, layer);
        });

        lua.set_function("setTransform", [this](int entityUID, float posX, float posY) {
           physicsEngine.setTransform(entityUID, posX, posY);



        });
    }
private:
    sol::state lua;
    EntityManager& entityManager;
    Dispatcher& dispatcher;
    RenderingEngine& renderingEngine;
    AnimationEngine& animationEngine;
    PhysicsEngine& physicsEngine;
};


#endif //BLOOM_ENGINE_SCRIPTINGENGINE_H
