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

            // Alphabetic keys
            "A", KeyCode::A,
            "B", KeyCode::B,
            "C", KeyCode::C,
            "D", KeyCode::D,
            "E", KeyCode::E,
            "F", KeyCode::F,
            "G", KeyCode::G,
            "H", KeyCode::H,
            "I", KeyCode::I,
            "J", KeyCode::J,
            "K", KeyCode::K,
            "L", KeyCode::L,
            "M", KeyCode::M,
            "N", KeyCode::N,
            "O", KeyCode::O,
            "P", KeyCode::P,
            "Q", KeyCode::Q,
            "R", KeyCode::R,
            "S", KeyCode::S,
            "T", KeyCode::T,
            "U", KeyCode::U,
            "V", KeyCode::V,
            "W", KeyCode::W,
            "X", KeyCode::X,
            "Y", KeyCode::Y,
            "Z", KeyCode::Z,

            // Numeric keys
            "NUM_1", KeyCode::NUM_1,
            "NUM_2", KeyCode::NUM_2,
            "NUM_3", KeyCode::NUM_3,
            "NUM_4", KeyCode::NUM_4,
            "NUM_5", KeyCode::NUM_5,
            "NUM_6", KeyCode::NUM_6,
            "NUM_7", KeyCode::NUM_7,
            "NUM_8", KeyCode::NUM_8,
            "NUM_9", KeyCode::NUM_9,
            "NUM_0", KeyCode::NUM_0,

            // Special keys
            "ESC", KeyCode::ESC,
            "TILDE", KeyCode::TILDE,
            "TAB", KeyCode::TAB,
            "CAPS", KeyCode::CAPS,
            "LSHIFT", KeyCode::LSHIFT,
            "LCTRL", KeyCode::LCTRL,
            "WINDOWS", KeyCode::WINDOWS,
            "LALT", KeyCode::LALT,
            "SPACE", KeyCode::SPACE,
            "RALT", KeyCode::RALT,
            "MENU", KeyCode::MENU,
            "RCTRL", KeyCode::RCTRL,
            "RSHIFT", KeyCode::RSHIFT,
            "ENTER", KeyCode::ENTER,
            "BACKSLASH", KeyCode::BACKSLASH,
            "BACKSPACE", KeyCode::BACKSPACE,

            // Function keys
            "F1", KeyCode::F1,
            "F2", KeyCode::F2,
            "F3", KeyCode::F3,
            "F4", KeyCode::F4,
            "F5", KeyCode::F5,
            "F6", KeyCode::F6,
            "F7", KeyCode::F7,
            "F8", KeyCode::F8,
            "F9", KeyCode::F9,
            "F10", KeyCode::F10,
            "F11", KeyCode::F11,
            "F12", KeyCode::F12,

            // Other keys
            "PRT_SC", KeyCode::PRT_SC,
            "INS", KeyCode::INS,
            "DEL", KeyCode::DEL,
            "SCRL_LK", KeyCode::SCRL_LK,
            "HOME", KeyCode::HOME,
            "END", KeyCode::END,
            "PAUSE", KeyCode::PAUSE,
            "PG_UP", KeyCode::PG_UP,
            "PG_DN", KeyCode::PG_DN,

            // Arrow keys
            "ARROW_LEFT", KeyCode::ARROW_LEFT,
            "ARROW_UP", KeyCode::ARROW_UP,
            "ARROW_DOWN", KeyCode::ARROW_DOWN,
            "ARROW_RIGHT", KeyCode::ARROW_RIGHT
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

    // Expose AnimationEngine functionality
    lua.set_function("triggerAnimationChange", [&](int entityUID, const std::string& state) {
        if(state == "movingUp") {
            std::cout << "[DEBUG] triggerAnimationChange called for: movingUp" << std::endl;
            animationEngine.startAnimation(entityUID, AnimationType::WalkCycleUP);
        } else if(state == "idle") {
            animationEngine.stopAnimation(entityUID, AnimationType::WalkCycleUP);  // Assuming you stop the same animation
        }
        if(state == "movingDown") {
            std::cout << "[DEBUG] triggerAnimationChange called for: movingDown" << std::endl;
            animationEngine.startAnimation(entityUID, AnimationType::WalkCycleDOWN);
        } else if(state == "idle") {
            animationEngine.stopAnimation(entityUID, AnimationType::WalkCycleDOWN);  // Assuming you stop the same animation
        }
        if(state == "movingLeft") {
            animationEngine.startAnimation(entityUID, AnimationType::WalkCycleLEFT);
        } else if(state == "idle") {
            animationEngine.stopAnimation(entityUID, AnimationType::WalkCycleLEFT);  // Assuming you stop the same animation
        }
        if(state == "movingRight") {
            animationEngine.startAnimation(entityUID, AnimationType::WalkCycleRIGHT);
        } else if(state == "idle") {
            animationEngine.stopAnimation(entityUID, AnimationType::WalkCycleRIGHT);  // Assuming you stop the same animation
        }
        // Add other states as necessary
    });


}


void ScriptingEngine::handleInput() {
    lua["handleInput"]();
}
