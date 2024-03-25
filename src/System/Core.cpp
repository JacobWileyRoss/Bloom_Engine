//
// Created by Jacob Ross on 3/24/24.
//

#include "../../include/System/Core.h"
#include <iostream>


Core::Core() : window(nullptr), isRunning(false), dispatcher(entityManager),
               physicsEngine(entityManager, dispatcher, deltaTime), inputProcessor(entityManager, dispatcher),
               renderingEngine(entityManager, dispatcher) {}

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

    std::cout << "[INFO] Creating window..." << std::endl;
    window = SDL_CreateWindow("Bloom Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
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
    dispatcher.addEventListener(EventType::Input, [this](const Event& inputEvent) {
        physicsEngine.handleInputEvent(inputEvent);
    });

    int newEntity = entityManager.createEntity();
    std::cout << "[INFO] Entity created successfully" << std::endl;
    entityManager.attachComponent(newEntity, new Player);
    std::cout << "[INFO] Entity assigned Player component" << std::endl;
    entityManager.attachComponent(newEntity, new Transform);
    std::cout << "[INFO] Entity assigned Transform component" << std::endl;
    entityManager.attachComponent(newEntity, new Physics);
    std::cout << "[INFO] Entity assigned Physics component" << std::endl;
    entityManager.attachComponent(newEntity, new Renderable);
    std::cout << "[INFO] Entity assigned Renderable component" << std::endl;
    entityManager.attachComponent(newEntity, new Sprite);
    std::cout << "[INFO] Entity assigned Sprite component" << std::endl;
    entityManager.attachComponent(newEntity, new Texture);
    std::cout << "[INFO] Entity assigned Texture component" << std::endl;
    renderingEngine.setTexture(entityManager.getEntity(newEntity), "../Game/Assets/bloomGuy.png");
    renderingEngine.setSprite(entityManager.getEntity(newEntity), 0, 0, 32, 32);


    newEntity = entityManager.createEntity();
    std::cout << "[INFO] Entity created successfully" << std::endl;
    entityManager.attachComponent(newEntity, new Transform);
    Transform& transform = entityManager.getEntityComponent<Transform>(entityManager.getEntity(newEntity), "Transform");
    transform.posX = 100;
    transform.posY = 100;
    std::cout << "[INFO] Entity assigned Transform component" << std::endl;
    entityManager.attachComponent(newEntity, new Physics);
    std::cout << "[INFO] Entity assigned Physics component" << std::endl;
    entityManager.attachComponent(newEntity, new Renderable);
    std::cout << "[INFO] Entity assigned Renderable component" << std::endl;
    entityManager.attachComponent(newEntity, new Sprite);
    std::cout << "[INFO] Entity assigned Sprite component" << std::endl;
    entityManager.attachComponent(newEntity, new Texture);
    std::cout << "[INFO] Entity assigned Texture component" << std::endl;
    renderingEngine.setTexture(entityManager.getEntity(newEntity), "../Game/Assets/enemy.png");
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
                    inputProcessor.ProcessInput();
                    break;
                case SDL_KEYUP:
                    inputProcessor.ProcessInput();
            }


        }
        physicsEngine.update(deltaTime);
        renderingEngine.update(entityManager.entities);
        renderingEngine.Render(entityManager.entities);
        SDL_Delay((uint32_t)(1000 / 60));
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
