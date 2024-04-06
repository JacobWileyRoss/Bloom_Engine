//
// Created by Jacob Ross on 3/24/24.
//

#ifndef BLOOM_ENGINE_CORE_H
#define BLOOM_ENGINE_CORE_H


#include <vector>
#include <SDL.h>
#include "../../vendor/imgui-docking/imgui.h"
#include "../../vendor/imgui-docking/imgui_internal.h"
#include "../../vendor/imgui-docking/backends/imgui_impl_sdl2.h"
#include "../../vendor/imgui-docking/backends/imgui_impl_sdlrenderer2.h"

#include "FileSystem.h"
#include "StateMachine.h"
#include "ScriptingEngine.h"
#include "EntityManager.h"
#include "Dispatcher.h"
#include "RenderingEngine.h"
#include "AnimationEngine.h"
#include "PhysicsEngine.h"
#include "CollisionEngine.h"
#include "InputProcessor.h"

#include "../Component/Player.h"
#include "../Component/Transform.h"
#include "../Component/Physics.h"
#include "../Component/Renderable.h"
#include "../Component/Sprite.h"
#include "../Component/Texture.h"
#include "../Component/Collider.h"

#include "../../Bloom_Editor/include/CodeEditor.h"
#include "../../Bloom_Editor/include/ConsoleLogWindow.h"
#include "../../Bloom_Editor/include/ConsoleStreamBuffer.h"
#include "../../Bloom_Editor/include/FileTree.h"

class Core
{
public:
    Core();
    ~Core();
    void Initialize();
    void MainLoop();
    void Shutdown();
    SDL_Window* GetWindow();

private:
    FileSystem fileSystem;
    sol::state lua;
    ScriptingEngine scriptingEngine;
    StateMachine stateMachine;
    EntityManager entityManager;
    Dispatcher dispatcher;
    InputProcessor inputProcessor;
    PhysicsEngine physicsEngine;
    RenderingEngine renderingEngine;
    AnimationEngine animationEngine;
    CollisionEngine collisionEngine;


    SDL_Window* window;
    SDL_Event event{};
    bool isRunning;
    float deltaTime{};
    std::time_t lastModifiedTimeLevel{};
};


#endif //BLOOM_ENGINE_CORE_H
