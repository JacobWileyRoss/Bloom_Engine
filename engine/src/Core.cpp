//
// Created by Jacob Ross on 3/24/24.
//

#include "BloomEngine/Core.h"
#include <iostream>
#include <sol/sol.hpp>

namespace BloomEngine{
    // engine Core's constructor which initializes the individual required systems
    Core::Core() : window(nullptr), isRunning(false), fileSystem(), stateMachine(entityManager, lua),
                   dispatcher(entityManager),
                   physicsEngine(entityManager, dispatcher, deltaTime),
                   inputProcessor(entityManager,dispatcher), renderingEngine(entityManager, dispatcher),
                   animationEngine(entityManager, dispatcher, deltaTime),
                   collisionEngine(entityManager, dispatcher),
                   scriptingEngine(lua, entityManager, dispatcher, renderingEngine, animationEngine, physicsEngine, collisionEngine){}

    void Core::Initialize() {
        // Initialize SDL2 using SDL_INIT_EVERYTHING
        std::cout << "[INFO] Initializing SDL..." << std::endl;
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
            std::cerr << "[ERROR] Failed to initialize SDL: " << SDL_GetError() << std::endl;
            return;
        }
        std::cout << "[INFO] SDL initialized successfully." << std::endl;

        // Initialize SDL_Image for use with PNG
        std::cout << "[INFO] Initializing SDL_Image..." << std::endl;
        IMG_Init(IMG_INIT_PNG);
        std::cout << "[INFO] SDL_Image initialized successfully" << std::endl;

        // Create an SDL window and define window size
        std::cout << "[INFO] Creating window..." << std::endl;
        window = SDL_CreateWindow("Bloom engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                  1920, 1080, SDL_WINDOW_SHOWN);
        if (!window) {
            std::cerr << "[ERROR] Failed to create window: " << SDL_GetError() << std::endl;
            SDL_Quit();
            return;
        }
        std::cout << "[INFO] Window created successfully." << std::endl;
        isRunning = true;

        // Initialize RenderingEngine and pass the SDL window
        RenderingEngine::Initialize(window);

        // PhysicsEngine and AnimationEngine registering to the dispatcher for Input and Collision events
        dispatcher.addEventListener(EventType::InputKeyDown, [this](const Event& inputEvent) {
            std::cout << "[INFO] Handling EventType::InputKeyDown" << std::endl;
            physicsEngine.handleInputEvent(inputEvent);
            animationEngine.handleInputEvent(inputEvent);
        });

        dispatcher.addEventListener(EventType::InputKeyUp, [this](const Event& inputEvent) {
            std::cout << "[INFO] Handling EventType::InputKeyUp" << std::endl;
            physicsEngine.handleInputEvent(inputEvent);
            animationEngine.handleInputEvent(inputEvent);
        });

        dispatcher.addEventListener(EventType::Collision, [this](const Event& collisionEvent) {
            std::cout << "[INFO] Handling EventType::Collision" << std::endl;
            physicsEngine.handleCollisionEvent(collisionEvent);
            animationEngine.handleInputEvent(collisionEvent);
        });

        // Load Lua script for current Level
        scriptingEngine.loadScript("../../Editor/Game/Levels/Level1.lua");

        // TODO review StateMachine and the relevance of changeState - does not affect hot reloading like I thought
        // Load GameplayState defined in the Level Lua script
        stateMachine.changeState("GameplayState");
    }


    void Core::Update() {
        //std::cout << "[INFO] Core::Update() Called!" << std::endl;
        uint32_t lastTime = SDL_GetTicks();
        while(SDL_PollEvent(&event) != 0) {
            uint32_t currentTime = SDL_GetTicks();
            deltaTime = (currentTime - lastTime) / 1000.f;
            lastTime = currentTime;
            if(event.type == SDL_QUIT) {
                isRunning = false;
            }
            switch (event.type) {
                case SDL_KEYDOWN:
                    inputProcessor.ProcessInput(event);
                    break;
                case SDL_KEYUP:
                    inputProcessor.ProcessInput(event);
            }
        }

        // FileSystem checks the Lua script for the date of last modification, if changed it reload the script this
        // Enables "Hot Reloading"
        fileSystem.checkAndReloadScript(scriptingEngine.getLuaState(), "../../Editor/Game/Levels/Level1.lua", lastModifiedTimeLevel);

        // All systems perform their own update() functions
        scriptingEngine.update(deltaTime);
        physicsEngine.update(deltaTime);
        collisionEngine.update();
        animationEngine.update(deltaTime);
        renderingEngine.update(entityManager.entities);

        // Render
        renderingEngine.Render(entityManager.entities);

    }

    void Core::HandleInput(SDL_Event event) {
        inputProcessor.ProcessInput(event);
    }

    void Core::Render() {
        renderingEngine.Render(entityManager.entities);
    }

// engine Core calls Shutdown() function to destroy SDL window
    void Core::Shutdown() {
        SDL_DestroyWindow(window);
        window = nullptr;
        std::cout << "[INFO] Quitting SDL..." << std::endl;
        SDL_Quit();
        std::cout << "[INFO] SDL quit successfully." << std::endl;
    }

    SDL_Window *Core::GetWindow() {
        return window;
    }

    SDL_Renderer* Core::GetRenderer() {
        return this->renderingEngine.GetRenderer();
    }

    SDL_Texture* Core::GetRenderTargetTexture() {
        return renderingEngine.GetRenderTargetTexture();
    }

// Core defualt destructor
    Core::~Core() = default;

}


