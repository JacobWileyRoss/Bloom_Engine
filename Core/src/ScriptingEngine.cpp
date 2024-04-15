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
    //std::cout << "[INFO] ScriptingEngine::update() called with deltaTime: " << deltaTime << std::endl;
    lua["update"](deltaTime);
}

void ScriptingEngine::loadScript(const std::string &filePath) {
    lua.script_file(filePath);
}

void ScriptingEngine::saveScript(const std::string& filePath, const std::string& data) {
    std::ofstream outFile(filePath);
    if (!outFile.is_open()) {
        std::cerr << "Failed to open file for writing: " << filePath << std::endl;
        return; // Consider how to handle errors, possibly by returning a success/failure status
    }
    outFile << data;
    outFile.close();
}

void ScriptingEngine::addEntity(int entityUID) {
    createdEntities.push_back(entityUID);
}

// This function "exposes" Engine functionality and data to the ScriptingEngine so that Lua can interact with the
// actual Engine itself
void ScriptingEngine::bindToLua() {
    /* Essential System's functionality exposed to Lua */

    // Expose the ComponentType to Lua
    lua["ComponentType"] = lua.create_table_with(
            "Animation", ComponentType::Animation,
            "Audio", ComponentType::Audio,
            "Camera", ComponentType::Camera,
            "Collider", ComponentType::Collider,
            "Event", ComponentType::Event,
            "Physics", ComponentType::Physics,
            "Player", ComponentType::Player,
            "Renderable", ComponentType::Renderable,
            "Sprite", ComponentType::Sprite,
            "Texture", ComponentType::Texture,
            "Transform", ComponentType::Transform
    );

    // Expose event types to Lua
    lua["EventType"] = lua.create_table_with(
            "InputKeyDown", EventType::InputKeyDown,
            "InputKeyUp", EventType::InputKeyUp,
            "Physics", EventType::Physics,
            "Collision", EventType::Collision,
            "Undefined", EventType::Undefined
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

    // Expose the KeyCode types to Lua
    lua["KeyCode"] = lua.create_table_with(
            "W", KeyCode::W,
            "A", KeyCode::A,
            "S", KeyCode::S,
            "D", KeyCode::D
    );

    // Expose game functions, entities, and components to Lua
    // Exposing a function to log messages from Lua:
    lua.set_function("logMessage", [](const std::string& message) {
        std::cout << message << std::endl;
    });

    // Expose functionality to Lua to save the script for serializing Lua game state
    lua.set_function("saveScript", [this](const std::string& filePath, const std::string& data) {
        saveScript(filePath, data);
    });

    lua.set_function("dispatchEvent", [this](int entityUID, EventType eventType, KeyCode keyCode) {
        EventData eventData = keyCode;
        Event event(entityUID, eventType, eventData);
        dispatcher.dispatchEvent(event);
    });

    // Exposing EntityManager's createEntity() functionality
    lua.set_function("createEntity", [this]() {
        int newEntity = entityManager.createEntity();
        createdEntities.push_back(newEntity);
        return newEntity;
    });

    lua.set_function("destroyEntities", [this]() {
        for(auto entity : createdEntities) {
            entityManager.destroyEntity(entity);
        }
        createdEntities.clear();
    });

    lua.set_function("attachComponent", [this](int entityUID, ComponentType componentType) {
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

    // Expose the function to Lua to modify the Physics component
    lua.set_function("setPhysics", [this](int entityUID, float dirX, float dirY, float speed) {
        physicsEngine.setPhysics(entityUID, dirX, dirY, speed);
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

    lua.set_function("setBank", [this](int entityUID, std::string bankPath) {
        std::cout << "[DEBUG] Lua called setBank(" << entityUID << ", " << bankPath << ")" << std::endl;
        audioEngine.SetBank(entityUID, bankPath);
    });

    lua.set_function("getEntityBank", [this](int entityUID) {
        audioEngine.getEntityBank(entityUID);
    });

    lua.set_function("loadBank", [this](std::string filepath) {
        audioEngine.LoadBank(filepath);
    });

    lua.set_function("loadEntityBank", [this](int entityUID) {
        audioEngine.LoadEntityBank(entityUID);
    });

    lua.set_function("unloadAllBanks", [this]() {
        audioEngine.UnloadAllBanks();
    });

    lua.set_function("playEvent", [this](std::string eventPath) {
        audioEngine.PlayEvent(eventPath);
    });

    lua.set_function("playEntityEvent", [this](int entityUID, const std::string& eventName, const std::string& eventPath) {
        audioEngine.PlayEvent(entityUID, eventName, eventPath);
    });

    lua.set_function("stopAllActiveAudioEvents", [this]() {
        audioEngine.StopAllActiveEvents();
    });

    lua.set_function("applyForce", [this](int entityUID, float x, float y) {
        physicsEngine.applyForce(entityUID, x, y);
    });

    // Expose the function to register key down callbacks
    lua.set_function("registerKeyDownCallback", [&](KeyCode keyCode, sol::function func) {
        inputProcessor.registerKeyDownCallback(keyCode, func);
    });

    // Expose the function to register key up callbacks
    lua.set_function("registerKeyUpCallback", [&](KeyCode keyCode, sol::function func) {
        inputProcessor.registerKeyUpCallback(keyCode, func);
    });

}


void ScriptingEngine::handleInput() {
    lua["handleInput"]();
}
