//
// Created by Jacob Ross on 3/24/24.
//

#include "../include/Core.h"
#include <iostream>


// Engine Core's constructor which initializes the individual required systems
Core::Core() : window(nullptr), isRunning(false), fileSystem(), stateMachine(entityManager, lua),
               editor(window, audioEngine, renderingEngine, entityManager, scriptingEngine, stateMachine),
               dispatcher(entityManager),
               physicsEngine(entityManager, dispatcher, deltaTime),
               inputProcessor(entityManager,dispatcher), renderingEngine(entityManager, dispatcher),
               animationEngine(entityManager, dispatcher, deltaTime),
               collisionEngine(entityManager, dispatcher),
               audioEngine(entityManager),
               scriptingEngine(lua, entityManager, dispatcher, renderingEngine, animationEngine,
                               physicsEngine, collisionEngine, audioEngine) {}

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
    // TODO determine best way to specify window size, should it be configured in Lua scripting?
    window = SDL_CreateWindow("Bloom Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
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

    // Initialize AudioEngine
    audioEngine.Initialize();

    // PhysicsEngine and AnimationEngine registering to the dispatcher for Input and Collision events
    dispatcher.addEventListener(EventType::InputKeyDown, [this](const Event& inputEvent) {
        std::cout << "[INFO] Handling EventType::InputKeyDown" << std::endl;
        physicsEngine.handleInputEvent(inputEvent);
        animationEngine.handleInputEvent(inputEvent);
        audioEngine.HandleInputEvent(inputEvent);
    });

    dispatcher.addEventListener(EventType::InputKeyUp, [this](const Event& inputEvent) {
        std::cout << "[INFO] Handling EventType::InputKeyUp" << std::endl;
        physicsEngine.handleInputEvent(inputEvent);
        animationEngine.handleInputEvent(inputEvent);
        audioEngine.HandleInputEvent(inputEvent);
    });

    dispatcher.addEventListener(EventType::Collision, [this](const Event& collisionEvent) {
        std::cout << "[INFO] Handling EventType::Collision" << std::endl;
        physicsEngine.handleCollisionEvent(collisionEvent);
        animationEngine.handleInputEvent(collisionEvent);
    });

    // Load Lua script for current Level
    scriptingEngine.setCurrentSelectedScript("../Editor/include/default.lua") ;
    scriptingEngine.loadScript(scriptingEngine.getCurrentSelectedScript());


    // TODO review StateMachine and the relevance of changeState - does not affect hot reloading like I thought
    // Load GameplayState defined in the Level Lua script
    stateMachine.changeState("GameplayState");
}

// Start the Engine's MainLoop function
void Core::MainLoop() {

    // Setup ImGui context
    std::cout << "[INFO] Initializing ImGui..." << std::endl;
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking

    // Setup Platform/Renderer bindings
    ImGui_ImplSDL2_InitForSDLRenderer(window, renderingEngine.GetRenderer());
    ImGui_ImplSDLRenderer2_Init(renderingEngine.GetRenderer());
    editor.Initialize();
    std::cout << "[INFO] ImGui initialized successfully" << std::endl;

    // Start the Core MainLoop()
    std::cout << "[INFO] MainLoop() Called!" << std::endl;
    uint32_t lastTime = SDL_GetTicks();
    while(isRunning) {
        uint32_t currentTime = SDL_GetTicks();
        deltaTime = (currentTime - lastTime) / 1000.f;
        lastTime = currentTime;
        while(SDL_PollEvent(&event) != 0) {

            // Editor event handling
            editor.Update(event);

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
        fileSystem.checkAndReloadScript(scriptingEngine.getLuaState(),
                                        scriptingEngine.getCurrentSelectedScript(), lastModifiedTimeLevel);

        // All systems perform their own update() functions
        physicsEngine.update(deltaTime);
        collisionEngine.update();
        animationEngine.update(deltaTime);
        renderingEngine.update(entityManager.entities);
        renderingEngine.Render(entityManager.entities);
        scriptingEngine.update(deltaTime);
        audioEngine.Update();

        //Lock to 60 FPS
        //SDL_Delay((uint32_t)(1000 / 60));

        editor.Render();
    }
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}

// Engine Core calls Shutdown() function to destroy SDL window
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

// Core default destructor
Core::~Core() = default;