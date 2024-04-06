//
// Created by Jacob Ross on 3/28/24.
//

#include "../include/ScriptingEngine.h"

void ScriptingEngine::initialize() {
    lua["initialize"]();
}

sol::state& ScriptingEngine::getLuaState() {
    return lua;
}

void ScriptingEngine::update(float deltaTime) {
    // Example: Call the "update" function defined in Lua, passing deltaTime
    lua["update"](deltaTime);
}

void ScriptingEngine::loadScript(const std::string &scriptPath) {
    lua.script_file(scriptPath);
}

// This function "exposes" Engine functionality and data to the ScriptingEngine so that Lua can interact with the
// actual Engine itself
void ScriptingEngine::bindToLua() {
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