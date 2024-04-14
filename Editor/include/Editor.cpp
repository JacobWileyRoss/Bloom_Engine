//
// Created by Jacob Ross on 4/5/24.
//

#include "Editor.h"

//SDL_Texture* bloomEngineSplashScreen = nullptr;

void Editor::Initialize() {
    auto& style = ImGui::GetStyle();
    style.Alpha = 1.0;
    style.WindowRounding = 3;
    style.GrabRounding = 1;
    style.GrabMinSize = 20;
    style.FrameRounding = 3;

    //style.Colors[ImGuiCol_Text] = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
    style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.00f, 0.40f, 0.41f, 1.00f);
    style.Colors[ImGuiCol_WindowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    style.Colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_Border] = ImVec4(255.0f, 255.0f, 255.0f, 0.3f);
    style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    style.Colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.10f, 0.10f, 0.66f);
    style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(255.0f, 0, 135.0f, 255.0f);
    style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.44f, 0.81f, 0.86f, 0.66f);
    style.Colors[ImGuiCol_TitleBg] = ImVec4(12.0f, 12.0f, 12.0f, 0.05f);
    style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.54f);
    style.Colors[ImGuiCol_TitleBgActive] = ImVec4(255.0f, 0, 135.0f, 0.5f);
    style.Colors[ImGuiCol_Tab] = ImVec4(255.0f, 0, 135.0f, 0.3f);
    style.Colors[ImGuiCol_TabActive] = ImVec4(255.0f, 0, 135.0f, 1.0f);
    style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(255.0f, 0, 135.0f, 0.6f);
    style.Colors[ImGuiCol_TabUnfocused] = ImVec4(255.0f, 0, 135.0f, 0.1f);
    style.Colors[ImGuiCol_TabHovered] = ImVec4(255.0f, 0, 200.0f, 0.5f);
    style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(255.0f, 0, 200.0f, 0.5f);
    style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(255.0f, 0, 135.0f, 0.6f);
    style.Colors[ImGuiCol_Button] = ImVec4(12.0f, 12.0f, 12.0f, 0.2f);
    style.Colors[ImGuiCol_ButtonHovered] = ImVec4(255.0f, 0, 200.0f, 0.5f);

    // Redirect cout and cerr to the custom stream buffer
//    std::cout.rdbuf(&consoleStreamBuffer);
//    std::cerr.rdbuf(&consoleStreamBuffer);

    // Load Bloom Engine logo for Viewport splash screen (when no camera component found)
    bloomEngineSplashScreen = IMG_LoadTexture(renderingEngine.GetRenderer(),
                                              "../Editor/assets/BloomEngine_Logo_002.png");
}

void Editor::Update(SDL_Event &event) {
    ImGui_ImplSDL2_ProcessEvent(&event);
}

void Editor::Render() {

    // Start ImGui rendering
    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    // Begin DockSpace
    ImGui::DockSpaceOverViewport();
    ImGuiID dockspace_id1 = ImGui::GetID("Dockspace1");
    ImGuiID dockspace_id2 = ImGui::GetID("Dockspace2");
    ImGuiID dockspace_id3 = ImGui::GetID("Dockspace3");
    ImGuiID dockspace_id4 = ImGui::GetID("Dockspace4");

    // Main Menu Bar
    if (ImGui::BeginMainMenuBar()) {
        // File Menu
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("New Level")) {
                ImGuiFileDialog ::Instance()->OpenDialog("SaveLevelDlgKey",
                                                         "Save New Level", ".lua");
            }
            if (ImGui::MenuItem("Load Level")) {
                // Open the file dialog when "Load Level" is clicked
                ImGuiFileDialog::Instance()->OpenDialog("LoadLevelDlgKey",
                                                        "Load Level", ".lua");
            }
            if (ImGui::MenuItem("Save Level")) {
                Serialize(scriptingEngine.getCurrentSelectedScript());
            }
            ImGui::EndMenu();
        }
        // TODO About menu is botched idk what I'm doing lol
        if (ImGui::BeginMenu("About")) {
            ImGui::SetNextWindowSize(ImVec2(100, 75));
            if(ImGui::BeginPopup("About", ImGuiWindowFlags_ChildWindow)) {
                ImGui::LabelText("About Bloom Engine", nullptr);
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }

    // Check if the dialog needs to be displayed and handled
    if (ImGuiFileDialog::Instance()->Display("SaveLevelDlgKey")) {
        // If the user selects a save path and clicks OK, the dialog will return true
        if (ImGuiFileDialog::Instance()->IsOk()) {
            std::string filePath = ImGuiFileDialog::Instance()->GetFilePathName();
            scriptingEngine.setCurrentSelectedScript(filePath);
            // Save the new level to the selected file path
            Serialize(filePath);
        }
        // Close the dialog after processing
        ImGuiFileDialog::Instance()->Close();
    }
    // Check if the dialog needs to be displayed
    if (ImGuiFileDialog::Instance()->Display("LoadLevelDlgKey")) {
        // If the user selects a file and clicks OK, the dialog will return true
        if (ImGuiFileDialog::Instance()->IsOk()) {
            auto filePath = ImGuiFileDialog::Instance()->GetFilePathName();
            // Now you can load the level from the selected file
            LoadLevel(filePath); // Assuming this is a function you've defined
        }

        // Close the dialog after processing (or if cancelled)
        ImGuiFileDialog::Instance()->Close();
    }

    // Render viewport
    ImVec2 viewportResolution(1280, 720);
    ImGui::SetNextWindowSize(viewportResolution); // Set the width and height of the next window
    ImGui::SetNextWindowSizeConstraints(viewportResolution, viewportResolution);
    ImGui::Begin("Viewport");
    if (renderingEngine.hasCameraEntity()) {
        // Usual game rendering logic
        ImTextureID texID = reinterpret_cast<ImTextureID>(renderingEngine.GetRenderTargetTexture());
        ImVec2 imageSize = ImVec2(viewportResolution.x, viewportResolution.y);
        ImGui::Image(texID, imageSize);
    } else {
        // Render the PNG image since no camera entity is present
        // Assuming splashTexture is your loaded SDL_Texture* for the PNG image
        ImTextureID splashTexID = reinterpret_cast<ImTextureID>(bloomEngineSplashScreen);
        // Adjust size as needed
        ImGui::Image(splashTexID, ImVec2(viewportResolution.x, viewportResolution.y));
    }
    ImGui::End();

    // Render FPS counter
    ImGui::Begin("Performance");
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate,
                ImGui::GetIO().Framerate);
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

    // Render Entity Manager
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
        scriptingEngine.addEntity(currentSelectedEntity);
        std::string operation = "local entity" + std::to_string(currentSelectedEntity) + " = createEntity()\n";
        operationsLog.logOperation(operation);
        std::cout << "[INFO] LUA COMMAND LOGGED: " << operation  << std::endl;
    }

    // Column 2: Component Attachment
    ImGui::NextColumn();
    ImGui::Text("Attach Component");
    ImGui::Separator();
    if (currentSelectedEntity != -1) {
        static int componentTypeIndex = 0;
        ComponentType componentTypes[] = {
                ComponentType::Animation, ComponentType::Camera, ComponentType::Collider,
                ComponentType::Event, ComponentType::Physics, ComponentType::Player,
                ComponentType::Renderable, ComponentType::Sprite, ComponentType::Texture,
                ComponentType::Transform
        };
        const char* componentTypeNames[] = {
                "Animation", "Camera", "Collider", "Event", "Physics",
                "Player", "Renderable", "Sprite", "Texture", "Transform"
        };
        ImGui::Combo("Component", &componentTypeIndex, componentTypeNames,
                     IM_ARRAYSIZE(componentTypeNames));
        if (ImGui::Button("Attach")) {
            // TODO attach will fail and crash if attaching Collider without a Physics component already attached
            // Other components were failing without a Transform, so I attach one by default during createEntity()
            entityManager.attachComponent(currentSelectedEntity, componentTypes[componentTypeIndex]);
            std::string operation = "attachComponent(" + std::to_string(currentSelectedEntity) +
                    ", ComponentType." + componentTypeNames[componentTypeIndex] + ")\n";
            operationsLog.logOperation(operation);
            std::cout << "[INFO] LUA COMMAND LOGGED: " << operation  << std::endl;
        }
    }

    // Column 3: Component Editing
    ImGui::NextColumn();
    ImGui::Text("Edit Components");
    ImGui::Separator();
    if (currentSelectedEntity != -1) {
        Entity& entity = entityManager.getEntity(currentSelectedEntity);
        ImGui::Text("Entity %d Components", currentSelectedEntity);
        std::vector<ComponentType> componentsToBeRemoved;
        for (const auto& compPair : entity.components) {
            ComponentType compType = compPair.first;
            std::string compName = componentTypeToString(compType);
            if (ImGui::TreeNode(compName.c_str())) {
                // Immediate UI for removing a component
                ImGui::SameLine(ImGui::GetWindowWidth() - 100); // Adjust based on your UI layout
                if (ImGui::Button(("Remove##" + compName).c_str())) {
                    componentsToBeRemoved.push_back(compType);
                }

                // Component-specific UI based on type
                switch (compType) {
                    case ComponentType::Animation: {
                        break;
                    }
                    case ComponentType::Camera: {
                        break;
                    }
                    case ComponentType::Collider: {
                        auto& collider = dynamic_cast<Collider&>(*compPair.second);
                        ImGui::InputInt("Position X", &collider.rect.x);
                        ImGui::InputInt("Position Y", &collider.rect.y);
                        ImGui::InputInt("Width", &collider.rect.w);
                        ImGui::InputInt("Height", &collider.rect.h);
                    }
                    case ComponentType::Physics: {
                        break;
                    }
                    case ComponentType::Player: {
                        break;
                    }
                    case ComponentType::Renderable: {
                        static int renderLayerIndex = 0;
                        RenderLayer renderLayers[] = {
                                RenderLayer::background, RenderLayer::character, RenderLayer::foreground
                        };
                        const char* renderLayerNames[] = {
                                "Background", "Character", "Foreground"
                        };
                        ImGui::Combo("Layer", &renderLayerIndex, renderLayerNames,
                                     IM_ARRAYSIZE(renderLayers));
                        if (ImGui::Button("Set Render Layer")) {
                            renderingEngine.setRenderLayer(currentSelectedEntity,
                                                           renderLayers[renderLayerIndex]);
                            std::string operation = "setRenderLayer(entity" + std::to_string(currentSelectedEntity)
                                    + ", " + renderLayerToString(renderLayers[renderLayerIndex]) + ")\n";
                            operationsLog.logOperation(operation);
                            std::cout << "[INFO] LUA COMMAND LOGGED: " << operation  << std::endl;
                        }
                        break;
                    }
                    case ComponentType::Sprite: {
                        auto& sprite = dynamic_cast<Sprite&>(*compPair.second);

                        // Assuming ImGui::InputFloat returns true when the field is edited and Enter key is pressed
                        bool posXChanged = ImGui::InputFloat("Position X", &sprite.rect.x,
                                                             0.0f, 0.0f, "%.3f",
                                                             ImGuiInputTextFlags_EnterReturnsTrue);
                        bool posYChanged = ImGui::InputFloat("Position Y", &sprite.rect.y,
                                                             0.0f, 0.0f, "%.3f",
                                                             ImGuiInputTextFlags_EnterReturnsTrue);
                        bool widthChanged = ImGui::InputFloat("Width", &sprite.rect.w,
                                                             0.0f, 0.0f, "%.3f",
                                                             ImGuiInputTextFlags_EnterReturnsTrue);
                        bool heightChanged = ImGui::InputFloat("Height", &sprite.rect.h,
                                                             0.0f, 0.0f, "%.3f",
                                                             ImGuiInputTextFlags_EnterReturnsTrue);
                        if (posXChanged || posYChanged || widthChanged || heightChanged) {
                            // Log the operation here
                            std::string operation = "setSprite(entity" + std::to_string(currentSelectedEntity) +
                                                    ", " + std::to_string(sprite.rect.x) + ", "
                                                    + std::to_string(sprite.rect.y) +
                                                      ", " + std::to_string(sprite.rect.w) +
                                                             ", " + std::to_string(sprite.rect.h) + ")\n";
                            operationsLog.logOperation(operation);
                            std::cout << "[INFO] LUA COMMAND LOGGED: " << operation << std::endl;
                        }
                        break;
                    }
                    case ComponentType::Texture: {
                        // Example: Text input for texture file path
                        static char filePath[256] = "";
                        //ImGui::InputText("Texture Path##Texture", filePath, sizeof(filePath));
                        if (ImGui::Button("Load Texture##Texture")) {
                            ImGuiFileDialog::Instance()->OpenDialog("ChooseTextureDlgKey", "Load Texture",
                                                                    ".png");
                        }


                        // Check if the dialog needs to be displayed
                        if (ImGuiFileDialog::Instance()->Display("ChooseTextureDlgKey")) {
                            // If the user selects a file and clicks OK, the dialog will return true
                            if (ImGuiFileDialog::Instance()->IsOk()) {
                                auto filePath = ImGuiFileDialog::Instance()->GetFilePathName();
                                // Now you can load the texture from the selected file
                                renderingEngine.setTexture(currentSelectedEntity, filePath);
                                std::string operation = "setTexture(entity" + std::to_string(currentSelectedEntity)
                                                        + ", \"" + filePath + "\")\n";
                                operationsLog.logOperation(operation);
                                std::cout << "[INFO] LUA COMMAND LOGGED: " << operation  << std::endl;
                            }

                            // Close the dialog after processing (or if cancelled)
                            ImGuiFileDialog::Instance()->Close();
                        }
                        break;
                    }
                    case ComponentType::Transform: {
                        auto& transform = dynamic_cast<Transform&>(*compPair.second);
                        // Assuming ImGui::InputFloat returns true when the field is edited and Enter key is pressed
                        bool posXChanged = ImGui::InputFloat("Position X", &transform.posX,
                                                             0.0f, 0.0f, "%.3f",
                                                             ImGuiInputTextFlags_EnterReturnsTrue);
                        bool posYChanged = ImGui::InputFloat("Position Y", &transform.posY,
                                                             0.0f, 0.0f, "%.3f",
                                                             ImGuiInputTextFlags_EnterReturnsTrue);
                        if (posXChanged || posYChanged) {
                            // Log the operation here
                            std::string operation = "setTransform(entity" + std::to_string(currentSelectedEntity) +
                                                    ", " + std::to_string(transform.posX) + ", "
                                                    + std::to_string(transform.posY) + ")\n";
                            operationsLog.logOperation(operation);
                            std::cout << "[INFO] LUA COMMAND LOGGED: " << operation << std::endl;
                        }
                        break;
                    }
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

    // Render console log window docked
    if (ImGui::Begin("Console Log")) {
        ImGui::DockBuilderDockWindow("Console Log", dockspace_id3);
        consoleLogWindow.ShowConsoleLogWindow(consoleStreamBuffer.GetLines());
    }
    ImGui::End();

    // Render Code Editor docked
    if (ImGui::Begin("Code Editor")) {
        ImGui::DockBuilderDockWindow("Code Editor", dockspace_id4);
        codeEditor.Render();
    }
    ImGui::End();

    // ImGui rendering
    ImGui::Render();
    SDL_RenderClear(renderingEngine.GetRenderer());
    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
    SDL_RenderPresent(renderingEngine.GetRenderer());
}

void Editor::ShutDown() {
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}

std::string Editor::Serialize(const std::string& filepath) {
    // Default Lua scripts for game states
    // TODO game state defaults need to be generated once then only updated with the rest of the script
    std::string defaultGameStates = R"(
MainMenuState = {}

function MainMenuState.enter()
    print("[INFO] Entering MainMenuState")
end

function MainMenuState.exit()
    print("Exiting MainMenuState")
end

function MainMenuState.update(deltaTime)
    -- Update logic here
end

function MainMenuState.render()
    -- Rendering logic here
end

GameplayState = {}

function GameplayState.enter()
    print("[INFO] Entering GameplayState")
end

function GameplayState.exit()
    print("Exiting GameplayStateState")
end

function GameplayState.update(deltaTime)
    -- Update logic here
end

function GameplayState.render()
    -- Rendering logic here
end

-- Register the state with a global or a specific Lua registry for states
GameStateRegistry = GameStateRegistry or {}
GameStateRegistry["MainMenuState"] = MainMenuState
GameStateRegistry["GameplayState"] = GameplayState
)";

    // Fetch all logged operations
    std::string loggedOperations = operationsLog.getLoggedOperations();

    // Encapsulate entity construction and component operations in a function
    std::string luaCodeForEntities = "function constructLevel()\n" + loggedOperations + "end\n";

    // Combine default game states with the constructLevel function
    std::string finalLuaScript = defaultGameStates + "\n" + luaCodeForEntities;

    // Write to file
    std::ofstream outFile(filepath);
    if (!outFile.is_open()) {
        std::cerr << "Failed to open file for writing: " << filepath << std::endl;
        return "";
    }
    outFile << finalLuaScript;
    outFile.close();

    return finalLuaScript; // Return the final Lua script for further use or verification
}



void Editor::LoadLevel(std::string filepath) {
    std::cout << "[INFO] LoadLevel() called" << std::endl;
    audioEngine.StopAllActiveEvents();
    audioEngine.UnloadAllBanks();
//    entityManager.entities.clear();
//    std::cout << "[INFO] Entities cleared" << std::endl;
    scriptingEngine.setCurrentSelectedScript(filepath);
    scriptingEngine.loadScript(filepath);
    stateMachine.changeState("GameplayState");
}
