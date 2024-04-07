//
// Created by Jacob Ross on 4/5/24.
//

#include "Editor.h"

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
    style.Colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    style.Colors[ImGuiCol_Border] = ImVec4(255.0f, 0, 135.0f, 0.3f);
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
    std::cout.rdbuf(&consoleStreamBuffer);
    std::cerr.rdbuf(&consoleStreamBuffer);

    bool editorRunning = true;
    SDL_Event event;




}

void Editor::Update(SDL_Event &event) {
    ImGui_ImplSDL2_ProcessEvent(&event);

    // FileSystem checks the Lua script for the date of last modification, if changed it reload the script this
    // Enables "Hot Reloading"
    //fileSystem.checkAndReloadScript(scriptingEngine.getLuaState(), "../Game/src/levels/Level1.lua", lastModifiedTimeLevel);

}

void Editor::Render() {
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

        ImGui::Combo("Component", &componentTypeIndex, componentTypeNames, IM_ARRAYSIZE(componentTypeNames));

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