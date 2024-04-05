//
// Created by Jacob Ross on 4/3/24.
//

#include <iostream>
#include <filesystem>

#include "../engine/include/BloomEngine/Core.h"
#include "../vendor/imgui-master/imgui.h"
#include "../vendor/imgui-master/backends/imgui_impl_sdl2.h"
#include "../vendor/imgui-master/backends/imgui_impl_sdlrenderer2.h"

void DisplayFileTree(const std::filesystem::path& path) {
//    if (!std::filesystem::exists(path) || !std::filesystem::is_directory(path)) {
//        ImGui::Text("Invalid directory");
//        return;
//    }

    ImGui::BeginChild("FileTree", ImVec2(0, 0), true);

    for (const auto& entry : std::filesystem::directory_iterator(path)) {
        const auto filename = entry.path().filename().string();
        if (std::filesystem::is_directory(entry.status())) {
            if (ImGui::TreeNode(filename.c_str())) {
                DisplayFileTree(entry.path()); // Recursive call for subdirectories
                ImGui::TreePop();
            }
        } else {
            ImGui::Text("%s", filename.c_str());
        }
    }

    ImGui::EndChild();
}

int main() {
    // Editor and Engine initialization
    BloomEngine::Core engine;
    engine.Initialize(); // Make sure SDL and the renderer are initialized here

    // Setup ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer bindings
    ImGui_ImplSDL2_InitForSDLRenderer(engine.GetWindow(), engine.GetRenderer());
    ImGui_ImplSDLRenderer2_Init(engine.GetRenderer());

    bool editorRunning = true;
    SDL_Event event;

    // Main loop
    while (editorRunning) {
        // Process SDL events
        while (SDL_PollEvent(&event)) {
            // Let ImGui handle the event first
            ImGui_ImplSDL2_ProcessEvent(&event);

            // Check if debug window is active and highlighted
            //bool DebugWindowActive = ImGui::IsWindowFocused(IMGUI_);


            // Check if ImGui wants to capture mouse or keyboard
            bool ImGuiWantsMouse = ImGui::GetIO().WantCaptureMouse;
            bool ImGuiWantsKeyboard = ImGui::GetIO().WantCaptureKeyboard;

            // If ImGui wants to capture mouse or keyboard, skip passing the event to the engine
            if (!ImGuiWantsMouse || !ImGuiWantsKeyboard) {
                // Pass the event to the engine
                engine.HandleInput(event);
            }

            if (event.type == SDL_QUIT) {
                editorRunning = false;
            }
        }

        // Perform game updates and rendering
        engine.Update();

        // Render ImGui
        ImGui_ImplSDLRenderer2_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();






        // Render game output
        engine.Render();
        ImVec2 gameResolution(1280, 720);
        ImGui::SetNextWindowSize(gameResolution); // Set the width and height of the next window
        ImGui::SetNextWindowSizeConstraints(gameResolution, gameResolution);
        ImGui::Begin("Viewport");
        ImTextureID texID = reinterpret_cast<ImTextureID>(engine.GetRenderTargetTexture());
        ImVec2 imageSize = ImVec2(gameResolution.x, gameResolution.y);
        ImGui::Image(texID, imageSize);
        ImGui::End();

        // Render project window

        ImGui::Begin("Project");
        ImGui::Text("File Tree");
        DisplayFileTree("../../editor/Game");
        ImGui::End();

        ImGui::Begin("Assets");
        ImGui::Text("Asset Browser");
        ImGui::End();

        // ImGui rendering
        ImGui::Render();
        SDL_RenderClear(engine.GetRenderer());
        ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
        SDL_RenderPresent(engine.GetRenderer());
    }






    // Cleanup
    engine.Shutdown();
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    return 0;
}