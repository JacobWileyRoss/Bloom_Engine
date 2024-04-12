//
// Created by Jacob Ross on 3/24/24.
//

/**
 * @file Core.h
 * @brief Header file for the Core class of the Bloom Engine.
 *
 * This file declares the Core class, which orchestrates the initialization, main loop,
 * and shutdown of the game engine. It aggregates all major engine subsystems such as rendering,
 * physics, scripting, and input handling.
 */

#ifndef BLOOM_ENGINE_CORE_H
#define BLOOM_ENGINE_CORE_H


#include <vector>
#include "../../../vendor/sdl2/2.30.1/include/SDL2/SDL.h"
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
#include "AudioEngine.h"

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
#include "../../Editor/include/Editor.h"

/**
 * @class Core
 * @brief Central class of the Bloom Engine
 *
 * The Core class is responsible for orchestrating the engine's subsystems,
 * managing the main loop, and handling initialization and shutdown processes.
 * It provides the primary interface for running the game engine.
 */
class Core
{
public:
    /**
 * @brief Constructor of the Core class.
 *
 * Initializes the engine's core systems and sets default states.
 */
    Core();

    /**
     * @brief Destructor of the Core class.
     *
     * Ensures the proper shutdown and cleanup of the engine's core systems.
     */
    ~Core();


    /**
    * @brief Initializes all subsystems of the game engine and creates the main window.
    *
    * This method sets up SDL, SDL_Image, creates the SDL window, initializes the rendering engine,
    * and sets up other subsystems like Physics Engine, Animation Engine, etc. It also initializes
    * ImGui for the editor functionalities.
    */
    void Initialize();

    /**
 * Contains the engine's main loop where all subsystem updates and rendering occur.
 * This loop runs until the engine is signaled to shut down.
 */
    void MainLoop();

    /**
 * Shuts down the engine, releasing all allocated resources and subsystems.
 * Ensures a clean exit from the application.
 */
    void Shutdown();

    /**
 * Retrieves the main window used by the engine.
 * @return A pointer to the SDL_Window used by the engine.
 */
    SDL_Window* GetWindow();

private:
    Editor editor; ///< The engine's editor system, handling UI and in-engine editing.
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
    AudioEngine audioEngine;

    SDL_Window* window; ///< Main SDL window for the application.
    SDL_Event event{};
    bool isRunning;
    float deltaTime{};
    std::time_t lastModifiedTimeLevel{};
    int currentSelectedEntity = -1; // Initialized to -1 to indicate no entity selected
};


#endif //BLOOM_ENGINE_CORE_H
