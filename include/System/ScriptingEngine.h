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
    explicit ScriptingEngine(sol::state& lua, EntityManager& entityManager, Dispatcher& dispatcher,
                             RenderingEngine& renderingEngine,
                             AnimationEngine& animationEngine,
                             PhysicsEngine& physicsEngine,
                             CollisionEngine& collisionEngine) :
                             lua(lua),
                             entityManager(entityManager),
                             dispatcher(dispatcher),
                             renderingEngine(renderingEngine),
                             animationEngine(animationEngine),
                             physicsEngine(physicsEngine),
                             collisionEngine(collisionEngine){
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
                "Camera", ComponentTypes::Camera,
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
        lua["AnimationType"] = lua.create_table_with(
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
        );

        // Expose game functions, entities, and components to Lua
        // Exposing a function to log messages from Lua:
        lua.set_function("logMessage", [](const std::string& message) {
            std::cout << message << std::endl;
        });

        // Exposing EntityManager's createEntity() functionality
        lua.set_function("createEntity", [this]() {
          int newEntity = entityManager.createEntity();
          luaCreatedEntities.push_back(newEntity);
            return newEntity;
        });

        lua.set_function("destroyEntities", [this]() {
            for(auto entity : luaCreatedEntities) {
                entityManager.destroyEntity(entity);
            }
            luaCreatedEntities.clear();
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

        lua.set_function("setCamera", [this](int entityUID, int posX, int posY, int width, int height) {
            renderingEngine.setCamera(entityUID, posX, posY, width, height);
        });

        lua.set_function("setBoundaryBox", [this](int entityUID, int posX, int posY, int width, int height) {
            collisionEngine.setBoundaryBox(entityUID, posX, posY, width, height);
        });

        lua.set_function("addFrame", [this](int entityUID, AnimationType animationType, const char* filename) {
            std::cout << "[DEBUG] ScriptingEngine addFrame() called" << std::endl;
            SDL_Texture* frame = IMG_LoadTexture(renderingEngine.GetRenderer(), filename);
            std::cout << "[DEBUG] ScriptingEngine frame loaded successfully" << std::endl;
            animationEngine.addFrame(entityUID, animationType, frame);
        });
    }
    ~ScriptingEngine() {
        std::cout << "[INFO] ScriptingEngine destructor called" << std::endl;
        luaCreatedEntities.clear();
    }
private:
    sol::state& lua;
    EntityManager& entityManager;
    Dispatcher& dispatcher;
    RenderingEngine& renderingEngine;
    AnimationEngine& animationEngine;
    PhysicsEngine& physicsEngine;
    CollisionEngine& collisionEngine;
    std::vector<int> luaCreatedEntities;
};


#endif //BLOOM_ENGINE_SCRIPTINGENGINE_H
