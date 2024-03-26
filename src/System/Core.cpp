//
// Created by Jacob Ross on 3/24/24.
//

#include "../../include/System/Core.h"
#include <iostream>


Core::Core() : window(nullptr), isRunning(false), dispatcher(entityManager),
               physicsEngine(entityManager, dispatcher, deltaTime),
               inputProcessor(entityManager,dispatcher), renderingEngine(entityManager, dispatcher),
               animationEngine(entityManager, dispatcher, deltaTime){}

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

    // TODO Entity creation should occur in a Level or State, not in the Core
    int newEntity = entityManager.createEntity();
    entityManager.attachComponent(newEntity, ComponentTypes::Player);
    entityManager.attachComponent(newEntity, ComponentTypes::Transform);
    entityManager.attachComponent(newEntity, ComponentTypes::Physics);
    entityManager.attachComponent(newEntity, ComponentTypes::Renderable);
    entityManager.attachComponent(newEntity, ComponentTypes::Sprite);
    entityManager.attachComponent(newEntity, ComponentTypes::Texture);
    entityManager.attachComponent(newEntity, ComponentTypes::Animation);
    auto& transform = entityManager.getEntityComponent<Transform>
            (newEntity, ComponentTypes::Transform);
    auto& sprite = entityManager.getEntityComponent<Sprite>
            (newEntity, ComponentTypes::Sprite);
    physicsEngine.setTransform(newEntity, 10, 60);
    renderingEngine.setSprite(newEntity, transform.posX, transform.posY, 96, 128);
    renderingEngine.setTexture(newEntity, "../Game/Assets/hero_WalkCycleDown1.png");
    renderingEngine.setRenderLayer(newEntity, RenderLayer::character);
    SDL_Texture* frameUP1 = IMG_LoadTexture(renderingEngine.GetRenderer(), "../Game/Assets/hero_WalkCycleUp1.png");
    SDL_Texture* frameUP2 = IMG_LoadTexture(renderingEngine.GetRenderer(), "../Game/Assets/hero_WalkCycleUp2.png");
    SDL_Texture* frameUP3 = IMG_LoadTexture(renderingEngine.GetRenderer(), "../Game/Assets/hero_WalkCycleUp3.png");
    SDL_Texture* frameUP4 = IMG_LoadTexture(renderingEngine.GetRenderer(), "../Game/Assets/hero_WalkCycleUp4.png");
    SDL_Texture* frameUP5 = IMG_LoadTexture(renderingEngine.GetRenderer(), "../Game/Assets/hero_WalkCycleUp5.png");
    SDL_Texture* frameDOWN1 = IMG_LoadTexture(renderingEngine.GetRenderer(), "../Game/Assets/hero_WalkCycleDown1.png");
    SDL_Texture* frameDOWN2 = IMG_LoadTexture(renderingEngine.GetRenderer(), "../Game/Assets/hero_WalkCycleDown2.png");
    SDL_Texture* frameDOWN3 = IMG_LoadTexture(renderingEngine.GetRenderer(), "../Game/Assets/hero_WalkCycleDown3.png");
    SDL_Texture* frameDOWN4 = IMG_LoadTexture(renderingEngine.GetRenderer(), "../Game/Assets/hero_WalkCycleDown4.png");
    SDL_Texture* frameDOWN5 = IMG_LoadTexture(renderingEngine.GetRenderer(), "../Game/Assets/hero_WalkCycleDown5.png");
    SDL_Texture* frameLEFT1 = IMG_LoadTexture(renderingEngine.GetRenderer(), "../Game/Assets/hero_WalkCycleLeft1.png");
    SDL_Texture* frameLEFT2 = IMG_LoadTexture(renderingEngine.GetRenderer(), "../Game/Assets/hero_WalkCycleLeft2.png");
    SDL_Texture* frameLEFT3 = IMG_LoadTexture(renderingEngine.GetRenderer(), "../Game/Assets/hero_WalkCycleLeft3.png");
    SDL_Texture* frameLEFT4 = IMG_LoadTexture(renderingEngine.GetRenderer(), "../Game/Assets/hero_WalkCycleLeft4.png");
    SDL_Texture* frameLEFT5 = IMG_LoadTexture(renderingEngine.GetRenderer(), "../Game/Assets/hero_WalkCycleLeft5.png");
    SDL_Texture* frameRIGHT1 = IMG_LoadTexture(renderingEngine.GetRenderer(), "../Game/Assets/hero_WalkCycleRight1.png");
    SDL_Texture* frameRIGHT2 = IMG_LoadTexture(renderingEngine.GetRenderer(), "../Game/Assets/hero_WalkCycleRight2.png");
    SDL_Texture* frameRIGHT3 = IMG_LoadTexture(renderingEngine.GetRenderer(), "../Game/Assets/hero_WalkCycleRight3.png");
    SDL_Texture* frameRIGHT4 = IMG_LoadTexture(renderingEngine.GetRenderer(), "../Game/Assets/hero_WalkCycleRight4.png");
    SDL_Texture* frameRIGHT5 = IMG_LoadTexture(renderingEngine.GetRenderer(), "../Game/Assets/hero_WalkCycleRight5.png");
    animationEngine.addFrame(newEntity, AnimationType::WalkCycleUP, frameUP1 );
    animationEngine.addFrame(newEntity, AnimationType::WalkCycleUP, frameUP2 );
    animationEngine.addFrame(newEntity, AnimationType::WalkCycleUP, frameUP3 );
    animationEngine.addFrame(newEntity, AnimationType::WalkCycleUP, frameUP4 );
    animationEngine.addFrame(newEntity, AnimationType::WalkCycleUP, frameUP5 );
    animationEngine.addFrame(newEntity, AnimationType::WalkCycleDOWN, frameDOWN1 );
    animationEngine.addFrame(newEntity, AnimationType::WalkCycleDOWN, frameDOWN2 );
    animationEngine.addFrame(newEntity, AnimationType::WalkCycleDOWN, frameDOWN3 );
    animationEngine.addFrame(newEntity, AnimationType::WalkCycleDOWN, frameDOWN4 );
    animationEngine.addFrame(newEntity, AnimationType::WalkCycleDOWN, frameDOWN5 );
    animationEngine.addFrame(newEntity, AnimationType::WalkCycleLEFT, frameLEFT1 );
    animationEngine.addFrame(newEntity, AnimationType::WalkCycleLEFT, frameLEFT2 );
    animationEngine.addFrame(newEntity, AnimationType::WalkCycleLEFT, frameLEFT3 );
    animationEngine.addFrame(newEntity, AnimationType::WalkCycleLEFT, frameLEFT4 );
    animationEngine.addFrame(newEntity, AnimationType::WalkCycleLEFT, frameLEFT5 );
    animationEngine.addFrame(newEntity, AnimationType::WalkCycleRIGHT, frameRIGHT1 );
    animationEngine.addFrame(newEntity, AnimationType::WalkCycleRIGHT, frameRIGHT2 );
    animationEngine.addFrame(newEntity, AnimationType::WalkCycleRIGHT, frameRIGHT3 );
    animationEngine.addFrame(newEntity, AnimationType::WalkCycleRIGHT, frameRIGHT4 );
    animationEngine.addFrame(newEntity, AnimationType::WalkCycleRIGHT, frameRIGHT5 );

    newEntity = entityManager.createEntity();
    entityManager.attachComponent(newEntity, ComponentTypes::Transform);
    entityManager.attachComponent(newEntity, ComponentTypes::Renderable);
    entityManager.attachComponent(newEntity, ComponentTypes::Sprite);
    entityManager.attachComponent(newEntity, ComponentTypes::Texture);
    renderingEngine.setSprite(newEntity, 0, 0, 1280, 720);
    renderingEngine.setTexture(newEntity, "../Game/Assets/background_DarkPath_Ritual_Scene.png");
    renderingEngine.setRenderLayer(newEntity, RenderLayer::background);
    physicsEngine.setTransform(newEntity, 0, 0);
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
        physicsEngine.update(deltaTime);
        //collisionEngine.update(entityManager);
        animationEngine.update(deltaTime);
        renderingEngine.update(entityManager.entities);
        renderingEngine.Render(entityManager.entities);
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
