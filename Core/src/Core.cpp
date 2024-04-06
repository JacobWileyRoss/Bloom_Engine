//
// Created by Jacob Ross on 3/24/24.
//

#include "../include/Core.h"
#include <iostream>


// Engine Core's constructor which initializes the individual required systems
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
    scriptingEngine.loadScript("../Game/src/levels/Level1.lua");

    // TODO review StateMachine and the relevance of changeState - does not affect hot reloading like I thought
    // Load GameplayState defined in the Level Lua script
    stateMachine.changeState("GameplayState");
}

// Start the Engine's MainLoop function
void Core::MainLoop() {
    // Editor initialization
    ConsoleLogWindow consoleLogWindow;
    FileTree fileTree;
    CodeEditor codeEditor;

    // Setup ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer bindings
    ImGui_ImplSDL2_InitForSDLRenderer(window, renderingEngine.GetRenderer());
    ImGui_ImplSDLRenderer2_Init(renderingEngine.GetRenderer());

    // Redirect cout and cerr to the custom stream buffer
    std::stringstream consoleBuffer;
    ConsoleStreamBuffer consoleStreamBuffer(std::cout);
    std::cout.rdbuf(&consoleStreamBuffer);
    std::cerr.rdbuf(&consoleStreamBuffer);

    bool editorRunning = true;
    SDL_Event event;

    std::cout << "[INFO] MainLoop() Called!" << std::endl;
    uint32_t lastTime = SDL_GetTicks();
    while(isRunning) {
        uint32_t currentTime = SDL_GetTicks();
        deltaTime = (currentTime - lastTime) / 1000.f;
        lastTime = currentTime;
        while(SDL_PollEvent(&event) != 0) {
            ImGui_ImplSDL2_ProcessEvent(&event);

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
        fileSystem.checkAndReloadScript(scriptingEngine.getLuaState(), "../Game/src/levels/Level1.lua", lastModifiedTimeLevel);

        // All systems perform their own update() functions
        physicsEngine.update(deltaTime);
        collisionEngine.update();
        animationEngine.update(deltaTime);
        renderingEngine.update(entityManager.entities);
        renderingEngine.Render(entityManager.entities);
        scriptingEngine.update(deltaTime);

        //Lock to 60 FPS
        //SDL_Delay((uint32_t)(1000 / 60));


        // Render ImGui
        ImGui_ImplSDLRenderer2_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();


        // Begin DockSpace
        //static ImGuiID dockspace_id = ImGui::DockSpaceOverViewport(nullptr, ImGuiDockNodeFlags_PassthruCentralNode);
        ImGui::DockSpaceOverViewport();
        ImGuiID dockspace_id1 = ImGui::GetID("Dockspace1");
        ImGuiID dockspace_id2 = ImGui::GetID("Dockspace2");
        ImGuiID dockspace_id3 = ImGui::GetID("Dockspace3");
        ImGuiID dockspace_id4 = ImGui::GetID("Dockspace4");

        //ImGui::ShowDemoWindow();


        // Render viewport
        ImVec2 viewportResolution(1280, 720);
        ImGui::SetNextWindowSize(viewportResolution); // Set the width and height of the next window
        ImGui::SetNextWindowSizeConstraints(viewportResolution, viewportResolution);
        ImGui::Begin("Viewport");
        ImGui::DockBuilderDockWindow("Viewport", dockspace_id1);
        ImTextureID texID = reinterpret_cast<ImTextureID>(renderingEngine.GetRenderTargetTexture());
        ImVec2 imageSize = ImVec2(viewportResolution.x, viewportResolution.y);
        ImGui::Image(texID, imageSize);
        ImGui::End();

        // Render FPS counter
        ImGui::Begin("Performance");
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();


        // Render project window docked
        ImGui::SetNextWindowSize(ImVec2(200, 400), ImGuiCond_FirstUseEver);
        if (ImGui::Begin("Project Browser")) {
            ImGui::DockBuilderDockWindow("Project Browser", dockspace_id2);
            fileTree.DisplayFileTree("../Game", codeEditor);
        }
        ImGui::End();

// Render Asset Browser docked
        if (ImGui::Begin("Asset Browser")) {
            ImGui::DockBuilderDockWindow("Asset Browser", dockspace_id2);
            fileTree.DisplayFileTree("../Game/assets", codeEditor);
        }
        ImGui::End();

        RenderEntityManager();

// Render console log window docked
        if (ImGui::Begin("Console Log")) {
            ImGui::DockBuilderDockWindow("Console Log", dockspace_id3);
            consoleLogWindow.ShowConsoleLogWindow(consoleStreamBuffer.GetLines());
        }
        ImGui::End();

// Render Code Editor docked
//        if (ImGui::Begin("Code Editor")) {
//            ImGui::DockBuilderDockWindow("Code Editor", dockspace_id4);
//            codeEditor.Render();
//        }
//        ImGui::End();

        // ImGui rendering
        ImGui::Render();
        SDL_RenderClear(renderingEngine.GetRenderer());
        ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
        SDL_RenderPresent(renderingEngine.GetRenderer());
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

void Core::RenderEntityManager() {
    ImGui::Begin("Entity Manager");

    // Split view
    ImGui::Columns(3, nullptr, false); // Updated to 3 columns for better UI distribution

    // Column 1: Entity List
    ImGui::Text("Entities");
    ImGui::Separator();
    for (const auto& entityPair : entityManager.entities) {
        bool is_selected = (currentSelectedEntity == entityPair.first);
        if (ImGui::Selectable(std::to_string(entityPair.first).c_str(), is_selected)) {
            currentSelectedEntity = entityPair.first;
        }
    }

    if (ImGui::Button("Create New Entity")) {
        currentSelectedEntity = entityManager.createEntity();
    }

    ImGui::NextColumn();

    // Column 2: Component Attachment
    ImGui::Text("Attach Component");
    ImGui::Separator();
    if (currentSelectedEntity != -1) {
        static int componentTypeIndex = 0;
        ComponentTypes componentTypes[] = {
                ComponentTypes::Animation, ComponentTypes::Camera, ComponentTypes::Collider,
                ComponentTypes::Event, ComponentTypes::Physics, ComponentTypes::Player,
                ComponentTypes::Renderable, ComponentTypes::Sprite, ComponentTypes::Texture,
                ComponentTypes::Transform
        };
        const char* componentTypeNames[] = {
                "Animation", "Camera", "Collider", "Event", "Physics",
                "Player", "Renderable", "Sprite", "Texture", "Transform"
        };

        ImGui::Combo("Component Type", &componentTypeIndex, componentTypeNames, IM_ARRAYSIZE(componentTypeNames));

        if (ImGui::Button("Attach")) {
            entityManager.attachComponent(currentSelectedEntity, componentTypes[componentTypeIndex]);
        }
    }

    ImGui::NextColumn();

    // Column 3: Component Editing
    ImGui::Text("Edit Components");
    ImGui::Separator();
    if (currentSelectedEntity != -1) {
        Entity& entity = entityManager.getEntity(currentSelectedEntity);
        ImGui::Text("Entity %d Components", currentSelectedEntity);

        std::vector<ComponentTypes> componentsToBeRemoved;
        for (const auto& compPair : entity.components) {
            ComponentTypes compType = compPair.first;
            std::string compName = componentTypeToString(compType);

            if (ImGui::TreeNode(compName.c_str())) {
                // Immediate UI for removing a component
                ImGui::SameLine(ImGui::GetWindowWidth() - 100); // Adjust based on your UI layout
                if (ImGui::Button(("Remove##" + compName).c_str())) {
                    componentsToBeRemoved.push_back(compType);
                }

                // Component-specific UI based on type
                switch (compType) {
                    case ComponentTypes::Transform: {
                        auto& transform = dynamic_cast<Transform&>(*compPair.second);
                        ImGui::InputFloat("Position X", &transform.posX);
                        ImGui::InputFloat("Position Y", &transform.posY);
                        break;
                    }
                    case ComponentTypes::Sprite: {
                        auto& sprite = dynamic_cast<Sprite&>(*compPair.second);
                        ImGui::InputFloat("Position X", &sprite.rect.x);
                        ImGui::InputFloat("Position Y", &sprite.rect.y);
                        ImGui::InputFloat("Width", &sprite.rect.w);
                        ImGui::InputFloat("Height", &sprite.rect.h);
                        break;
                    }
                    case ComponentTypes::Texture: {
                        // Example: Text input for texture file path
                        static char filePath[256] = "";
                        ImGui::InputText("Texture Path##Texture", filePath, sizeof(filePath));
                        if (ImGui::Button("Load Texture##Texture")) {
                            renderingEngine.setTexture(currentSelectedEntity, filePath);
                        }
                        break;
                    }
                        // Additional component types...
                }
                ImGui::TreePop();
            }
        }

        // Process pending removals after UI loop to avoid iterator invalidation
        for (auto compType : componentsToBeRemoved) {
            entityManager.removeComponent(currentSelectedEntity, compType);
        }
    }

    ImGui::End();
}



// Core default destructor
Core::~Core() = default;
