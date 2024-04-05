//
// Created by Jacob Ross on 4/3/24.
//

#include <iostream>

#include "../engine/include/BloomEngine/Core.h"
#include "../vendor/imgui-docking/imgui.h"
#include "../vendor/imgui-docking/backends/imgui_impl_sdl2.h"
#include "../vendor/imgui-docking/backends/imgui_impl_sdlrenderer2.h"
#include "../vendor/imgui-docking/imgui_internal.h"
#include "include/ConsoleStreamBuffer.h"
#include "include/ConsoleLogWindow.h"
#include "include/FileTree.h"
#include "include/CodeEditor.h"


int main() {
    // Engine initialization
    BloomEngine::Core engine;
    engine.Initialize(); // Make sure SDL and the renderer are initialized here

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
    ImGui_ImplSDL2_InitForSDLRenderer(engine.GetWindow(), engine.GetRenderer());
    ImGui_ImplSDLRenderer2_Init(engine.GetRenderer());

    // Redirect cout and cerr to the custom stream buffer
    std::stringstream consoleBuffer;
    ConsoleStreamBuffer consoleStreamBuffer(std::cout);
    std::cout.rdbuf(&consoleStreamBuffer);
    std::cerr.rdbuf(&consoleStreamBuffer);

    bool editorRunning = true;
    SDL_Event event;

    // Main loop
    while (editorRunning) {
        // Process SDL events
        while (SDL_PollEvent(&event)) {
            // Let ImGui handle the event first
            ImGui_ImplSDL2_ProcessEvent(&event);
            engine.HandleInput(event);

            // Check if debug window is active and highlighted
            //bool DebugWindowActive = ImGui::IsWindowFocused(IMGUI_);

            // Check if ImGui wants to capture mouse or keyboard
            bool ImGuiWantsMouse = ImGui::GetIO().WantCaptureMouse;
            bool ImGuiWantsKeyboard = ImGui::GetIO().WantCaptureKeyboard;

            // If ImGui wants to capture mouse or keyboard, skip passing the event to the engine
            if (!ImGuiWantsMouse && !ImGuiWantsKeyboard) {
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


        // Begin DockSpace
        //static ImGuiID dockspace_id = ImGui::DockSpaceOverViewport(nullptr, ImGuiDockNodeFlags_PassthruCentralNode);
        ImGui::DockSpaceOverViewport();
        ImGuiID dockspace_id1 = ImGui::GetID("Dockspace1");
        ImGuiID dockspace_id2 = ImGui::GetID("Dockspace2");
        ImGuiID dockspace_id3 = ImGui::GetID("Dockspace3");
        ImGuiID dockspace_id4 = ImGui::GetID("Dockspace4");


        // Render engine output
        engine.Render();

        // Render viewport
        ImVec2 viewportResolution(960, 540);
        ImGui::SetNextWindowSize(viewportResolution); // Set the width and height of the next window
        ImGui::SetNextWindowSizeConstraints(viewportResolution, viewportResolution);
        ImGui::Begin("Viewport");
        ImGui::DockBuilderDockWindow("Viewport", dockspace_id1);
        ImTextureID texID = reinterpret_cast<ImTextureID>(engine.GetRenderTargetTexture());
        ImVec2 imageSize = ImVec2(viewportResolution.x, viewportResolution.y);
        ImGui::Image(texID, imageSize);
        ImGui::End();


        // Render project window docked
        ImGui::SetNextWindowSize(ImVec2(200, 400), ImGuiCond_FirstUseEver);
        if (ImGui::Begin("Project Browser")) {
            ImGui::DockBuilderDockWindow("Project Browser", dockspace_id2);
            fileTree.DisplayFileTree("../../editor/Game", codeEditor);
        }
        ImGui::End();

// Render Asset Browser docked
        if (ImGui::Begin("Asset Browser")) {
            ImGui::DockBuilderDockWindow("Asset Browser", dockspace_id2);
            fileTree.DisplayFileTree("../../editor/Game/Assets", codeEditor);
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
