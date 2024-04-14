//
// Created by Jacob Ross on 4/5/24.
//

#ifndef BLOOM_ENGINE_EDITOR_H
#define BLOOM_ENGINE_EDITOR_H


#include <iostream>
#include "../../vendor/imgui-docking/imgui.h"
#include "../../vendor/imgui-docking/imgui_internal.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
#include "../../../vendor/sdl2/2.30.1/include/SDL2/SDL_events.h"
#include "../../vendor/ImGuiFileDialog-master/ImGuiFileDialog.h"
#include "OperationsLog.h"

#include "../../Core//include/AudioEngine.h"
#include "../../Core/include/FileSystem.h"
#include "../../Core/include/RenderingEngine.h"
#include "../../Core/include/ScriptingEngine.h"
#include "../../Core/include/StateMachine.h"
#include "ConsoleLogWindow.h"
#include "ConsoleStreamBuffer.h"
#include "FileTree.h"
#include "CodeEditor.h"



class Editor {
public:
    Editor(SDL_Window* window, AudioEngine& audioEngine, RenderingEngine& renderingEngine, EntityManager& entityManager,
           ScriptingEngine& scriptingEngine, StateMachine& stateMachine) : audioEngine(audioEngine), renderingEngine(renderingEngine), entityManager(entityManager),
            scriptingEngine(scriptingEngine), stateMachine(stateMachine), window(window), consoleLogWindow(), consoleStreamBuffer(std::cout),
            fileTree(), codeEditor(){};
    void Initialize();
    void Update(SDL_Event &event);
    void Render();
    std::string Serialize(const std::string& filepath);
    void LoadLevel(std::string filepath);
    void ShutDown();

private:
    SDL_Window* window;
    AudioEngine& audioEngine;
    RenderingEngine& renderingEngine;
    EntityManager& entityManager;
    ScriptingEngine& scriptingEngine;
    FileSystem fileSystem;
    StateMachine& stateMachine;
    int currentSelectedEntity = -1; // Initialized to -1 to indicate no entity selected
    ConsoleLogWindow consoleLogWindow;
    FileTree fileTree;
    CodeEditor codeEditor;
    std::time_t lastModifiedTimeLevel{};
    std::stringstream consoleBuffer;
    ConsoleStreamBuffer consoleStreamBuffer;
    OperationsLog operationsLog;
    SDL_Texture* bloomEngineSplashScreen;
};


#endif //BLOOM_ENGINE_EDITOR_H
