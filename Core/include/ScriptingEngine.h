//
// Created by Jacob Ross on 3/28/24.
//

#ifndef BLOOM_ENGINE_SCRIPTINGENGINE_H
#define BLOOM_ENGINE_SCRIPTINGENGINE_H

#include <iostream>
#include <fstream>
#include <string>
#include <../../../vendor/sol2/include/sol/sol.hpp>
#include "FileSystem.h"
#include "AudioEngine.h"
#include "EntityManager.h"
#include "PhysicsEngine.h"
#include "RenderingEngine.h"
#include "AnimationEngine.h"
#include "CollisionEngine.h"
#include "Animation.h"

class ScriptingEngine {
public:
    explicit ScriptingEngine(sol::state& lua, EntityManager& entityManager, Dispatcher& dispatcher,
                             RenderingEngine& renderingEngine,
                             AnimationEngine& animationEngine,
                             PhysicsEngine& physicsEngine,
                             CollisionEngine& collisionEngine,
                             AudioEngine& audioEngine) :
                             lua(lua),
                             entityManager(entityManager),
                             dispatcher(dispatcher),
                             renderingEngine(renderingEngine),
                             animationEngine(animationEngine),
                             physicsEngine(physicsEngine),
                             collisionEngine(collisionEngine),
                             audioEngine(audioEngine){
        lua.open_libraries(sol::lib::base, sol::lib::math, sol::lib::table);
        bindToLua();
    }

    void initialize();
    sol::state& getLuaState();
    void update(float deltaTime);
    void loadScript(const std::string& filePath);
    void saveScript(const std::string& filePath, const std::string& data);
    void bindToLua();
    std::string getCurrentSelectedScript() {return currentSelectedScript;};
    void setCurrentSelectedScript(std::string filepath) {
        currentSelectedScript = filepath;
    }
    void addEntity(int entityUID);

    ~ScriptingEngine() {
        std::cout << "[INFO] ScriptingEngine destructor called" << std::endl;
        createdEntities.clear();
    }
private:
    sol::state& lua;
    EntityManager& entityManager;
    Dispatcher& dispatcher;
    RenderingEngine& renderingEngine;
    AnimationEngine& animationEngine;
    PhysicsEngine& physicsEngine;
    CollisionEngine& collisionEngine;
    std::vector<int> createdEntities;
    std::string currentSelectedScript;
    AudioEngine& audioEngine;

};


#endif //BLOOM_ENGINE_SCRIPTINGENGINE_H
