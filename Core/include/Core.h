//
// Created by Jacob Ross on 3/24/24.
//

#ifndef BLOOM_ENGINE_CORE_H
#define BLOOM_ENGINE_CORE_H


#include <vector>
#include <SDL.h>
#include "../../vendor/imgui-docking/imgui.h"
#include "../../vendor/imgui-docking/imgui_internal.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"

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

#include "Player.h"
#include "Transform.h"
#include "Physics.h"
#include "Renderable.h"
#include "Sprite.h"
#include "Texture.h"
#include "Collider.h"

#include "../../Editor/include/CodeEditor.h"
#include "../../Editor/include/ConsoleLogWindow.h"
#include "../../Editor/include/ConsoleStreamBuffer.h"
#include "../../Editor/include/FileTree.h"

class Core
{
public:
    Core();
    ~Core();
    void Initialize();
    void MainLoop();
    void Shutdown();
    SDL_Window* GetWindow();
    void RenderEntityManager();

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
    int currentSelectedEntity = -1; // Initialized to -1 to indicate no entity selected

};


#endif //BLOOM_ENGINE_CORE_H
