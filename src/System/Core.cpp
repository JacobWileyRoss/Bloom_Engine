//
// Created by Jacob Ross on 3/24/24.
//

#include "../../include/System/Core.h"
#include <iostream>
#include <sol/sol.hpp>


Core::Core() : window(nullptr), isRunning(false), fileSystem(), stateMachine(entityManager, lua),
                dispatcher(entityManager),
                physicsEngine(entityManager, dispatcher, deltaTime),
                inputProcessor(entityManager,dispatcher), renderingEngine(entityManager, dispatcher),
                animationEngine(entityManager, dispatcher, deltaTime),
                collisionEngine(entityManager, dispatcher),
                scriptingEngine(lua, entityManager, dispatcher, renderingEngine, animationEngine, physicsEngine, collisionEngine){}

void Core::Initialize() {
    // Load Lua script for game logic
    //scriptingEngine.loadScript("../include/System/game_logic.lua");
    scriptingEngine.initialize();



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

    std::cout << "[INFO] Creating window..." << std::endl;
    window = SDL_CreateWindow("Bloom Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              1280, 720, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "[ERROR] Failed to create window: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return;
    }
    std::cout << "[INFO] Window created successfully." << std::endl;
    isRunning = true;

    RenderingEngine::Initialize(window);


    // PhysicsEngine subscribes to Dispatcher registering interest in Input event types and adds handleInputEvent()
    // as a callback function
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


    scriptingEngine.loadScript("../Game/Levels/Level1.lua");


    stateMachine.changeState("GameplayState");
}

void Core::MainLoop() {
    std::cout << "[INFO] MainLoop() Called!" << std::endl;
    uint32_t lastTime = SDL_GetTicks();
    while(isRunning) {
        uint32_t currentTime = SDL_GetTicks();
        deltaTime = (currentTime - lastTime) / 1000.f;
        lastTime = currentTime;
        while(SDL_PollEvent(&event) != 0) {
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
        fileSystem.checkAndReloadScript(scriptingEngine.getLuaState(), "../Game/Levels/Level1.lua", lastModifiedTimeLevel);
        physicsEngine.update(deltaTime);
        collisionEngine.update();
        animationEngine.update(deltaTime);
        renderingEngine.update(entityManager.entities);
        renderingEngine.Render(entityManager.entities);
        scriptingEngine.update(deltaTime);
        //SDL_Delay((uint32_t)(1000 / 60));
    }
}

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

Core::~Core() = default;
