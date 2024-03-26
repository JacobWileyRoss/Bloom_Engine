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
                              1920, 1080, SDL_WINDOW_SHOWN);
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
    renderingEngine.setSprite(newEntity, transform.posX, transform.posY, 96, 128);
    renderingEngine.setTexture(newEntity, "../Game/Assets/hero_WalkCycleDown1.png");
    renderingEngine.setRenderLayer(newEntity, RenderLayer::character);
    SDL_Texture* frameUP1 = IMG_LoadTexture(renderingEngine.GetRenderer(), "../Game/Assets/hero_WalkCycleUP1.png");
    SDL_Texture* frameUP2 = IMG_LoadTexture(renderingEngine.GetRenderer(), "../Game/Assets/hero_WalkCycleUP2.png");
    SDL_Texture* frameUP3 = IMG_LoadTexture(renderingEngine.GetRenderer(), "../Game/Assets/hero_WalkCycleUP3.png");
    SDL_Texture* frameUP4 = IMG_LoadTexture(renderingEngine.GetRenderer(), "../Game/Assets/hero_WalkCycleUP4.png");
    SDL_Texture* frameUP5 = IMG_LoadTexture(renderingEngine.GetRenderer(), "../Game/Assets/hero_WalkCycleUP5.png");
    SDL_Texture* frameDOWN1 = IMG_LoadTexture(renderingEngine.GetRenderer(), "../Game/Assets/hero_WalkCycleDOWN1.png");
    SDL_Texture* frameDOWN2 = IMG_LoadTexture(renderingEngine.GetRenderer(), "../Game/Assets/hero_WalkCycleDOWN2.png");
    SDL_Texture* frameDOWN3 = IMG_LoadTexture(renderingEngine.GetRenderer(), "../Game/Assets/hero_WalkCycleDOWN3.png");
    SDL_Texture* frameDOWN4 = IMG_LoadTexture(renderingEngine.GetRenderer(), "../Game/Assets/hero_WalkCycleDOWN4.png");
    SDL_Texture* frameDOWN5 = IMG_LoadTexture(renderingEngine.GetRenderer(), "../Game/Assets/hero_WalkCycleDOWN5.png");
    SDL_Texture* frameLEFT1 = IMG_LoadTexture(renderingEngine.GetRenderer(), "../Game/Assets/hero_WalkCycleLEFT1.png");
    SDL_Texture* frameLEFT2 = IMG_LoadTexture(renderingEngine.GetRenderer(), "../Game/Assets/hero_WalkCycleLEFT2.png");
    SDL_Texture* frameLEFT3 = IMG_LoadTexture(renderingEngine.GetRenderer(), "../Game/Assets/hero_WalkCycleLEFT3.png");
    SDL_Texture* frameLEFT4 = IMG_LoadTexture(renderingEngine.GetRenderer(), "../Game/Assets/hero_WalkCycleLEFT4.png");
    SDL_Texture* frameLEFT5 = IMG_LoadTexture(renderingEngine.GetRenderer(), "../Game/Assets/hero_WalkCycleLEFT5.png");
    SDL_Texture* frameRIGHT1 = IMG_LoadTexture(renderingEngine.GetRenderer(), "../Game/Assets/hero_WalkCycleRIGHT1.png");
    SDL_Texture* frameRIGHT2 = IMG_LoadTexture(renderingEngine.GetRenderer(), "../Game/Assets/hero_WalkCycleRIGHT2.png");
    SDL_Texture* frameRIGHT3 = IMG_LoadTexture(renderingEngine.GetRenderer(), "../Game/Assets/hero_WalkCycleRIGHT3.png");
    SDL_Texture* frameRIGHT4 = IMG_LoadTexture(renderingEngine.GetRenderer(), "../Game/Assets/hero_WalkCycleRIGHT4.png");
    SDL_Texture* frameRIGHT5 = IMG_LoadTexture(renderingEngine.GetRenderer(), "../Game/Assets/hero_WalkCycleRIGHT5.png");
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
    transform = entityManager.getEntityComponent<Transform>
            (newEntity, ComponentTypes::Transform);
    entityManager.attachComponent(newEntity, ComponentTypes::Physics);
    entityManager.attachComponent(newEntity, ComponentTypes::Renderable);
    entityManager.attachComponent(newEntity, ComponentTypes::Sprite);
    entityManager.attachComponent(newEntity, ComponentTypes::Texture);
    renderingEngine.setSprite(newEntity, 100, 100, 192, 256);
    renderingEngine.setTexture(newEntity, "../Game/Assets/statue_DarkEnchantedKnight001.png");
    renderingEngine.setRenderLayer(newEntity, RenderLayer::foreground);
    physicsEngine.setTransform(newEntity, 864, 412);




    int windowWidth = 1920;
    int windowHeight = 1080;
    int tileWidth = 128;
    int tileHeight = 128;

// Calculate number of tiles needed horizontally and vertically
    int tilesX = windowWidth / tileWidth;
    int tilesY = windowHeight / tileHeight;

// Adjust for any partial tile spaces at the edges
    if (windowWidth % tileWidth != 0) tilesX++;
    if (windowHeight % tileHeight != 0) tilesY++;

// Loop through each tile position
    for (int y = 0; y < tilesY; y++) {
        for (int x = 0; x < tilesX; x++) {
            int newEntity = entityManager.createEntity();
            entityManager.attachComponent(newEntity, ComponentTypes::Transform);
            entityManager.attachComponent(newEntity, ComponentTypes::Renderable);
            entityManager.attachComponent(newEntity, ComponentTypes::Sprite);
            entityManager.attachComponent(newEntity, ComponentTypes::Texture);

            // Calculate the position for each tile
            int posX = x * tileWidth;
            int posY = y * tileHeight;

            // Assuming setTransform is a method you'll add to physicsEngine
            // similar to setSprite in renderingEngine, for setting up initial position
            physicsEngine.setTransform(newEntity, posX, posY);
            renderingEngine.setSprite(newEntity, posX, posY, tileWidth, tileHeight);
            renderingEngine.setTexture(newEntity, "../Game/Assets/ground_ForestPath001.png");
            renderingEngine.setRenderLayer(newEntity, RenderLayer::background); // Assuming Background is a valid enum value
        }
    }



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
