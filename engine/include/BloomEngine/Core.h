//
// Created by Jacob Ross on 3/24/24.
//

#ifndef BLOOM_ENGINE_CORE_H
#define BLOOM_ENGINE_CORE_H


#include <vector>
#include <SDL.h>
#include <sol/state.hpp>

#include "FileSystem.h"
#include "StateMachine.h"
#include "ScriptingEngine.h"
#include "EntityManager.h"
#include "Dispatcher.h"
#include "RenderingEngine.h"
#include "AnimationEngine.h"
#include "PhysicsEngine.h"
#include "CollisionEngine.h"
#include "InputProcessor.h"

#include "Player.h"
#include "Transform.h"
#include "Physics.h"
#include "Renderable.h"
#include "Sprite.h"
#include "Texture.h"
#include "Collider.h"

namespace BloomEngine{
    class Core
    {
    public:
        Core();
        ~Core();
        void Initialize();
        void Update();
        void HandleInput(SDL_Event event);
        void Render();
        void Shutdown();
        SDL_Window* GetWindow();
        SDL_Renderer* GetRenderer();
        SDL_Texture* GetRenderTargetTexture();

    private:
        FileSystem fileSystem;
        sol::state lua;
        ScriptingEngine scriptingEngine;
        StateMachine stateMachine;
        EntityManager entityManager;
        Dispatcher dispatcher;
        InputProcessor inputProcessor;
        PhysicsEngine physicsEngine;
        RenderingEngine renderingEngine;
        AnimationEngine animationEngine;
        CollisionEngine collisionEngine;


        SDL_Window* window;
        SDL_Event event{};
        bool isRunning;
        float deltaTime{};
        std::time_t lastModifiedTimeLevel{};
    };
}



#endif //BLOOM_ENGINE_CORE_H
