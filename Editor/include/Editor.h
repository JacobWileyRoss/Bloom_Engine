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
#include "../../Core/include/RenderingEngine.h"
#include "../../Core/include/FileSystem.h"
#include "ConsoleLogWindow.h"
#include "ConsoleStreamBuffer.h"
#include "FileTree.h"
#include "CodeEditor.h"
#include "../../Core/include/ScriptingEngine.h"
#include "SDL_events.h"


class Editor {
public:
    Editor(SDL_Window* window, RenderingEngine& renderingEngine, EntityManager& entityManager, ScriptingEngine& scriptingEngine) : renderingEngine(renderingEngine), entityManager(entityManager),
    scriptingEngine(scriptingEngine), window(window), consoleLogWindow(), consoleStreamBuffer(std::cout), fileTree(), codeEditor(){};
    void Initialize();
    void Update(SDL_Event &event);
    void Render();
    void ShutDown();

private:
    SDL_Window* window;
    RenderingEngine& renderingEngine;
    EntityManager& entityManager;
    ScriptingEngine& scriptingEngine;
    FileSystem fileSystem;
    int currentSelectedEntity = -1; // Initialized to -1 to indicate no entity selected
    ConsoleLogWindow consoleLogWindow;
    FileTree fileTree;
    CodeEditor codeEditor;
    std::time_t lastModifiedTimeLevel{};
    std::stringstream consoleBuffer;
    ConsoleStreamBuffer consoleStreamBuffer;





};


#endif //BLOOM_ENGINE_EDITOR_H
