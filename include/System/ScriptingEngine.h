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

    void initialize();
    sol::state& getLuaState();
    void update(float deltaTime);
    void loadScript(const std::string& scriptPath);
    void bindToLua();

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
