//
// Created by Jacob Ross on 3/24/24.
//

#ifndef BLOOM_ENGINE_CORE_H
#define BLOOM_ENGINE_CORE_H


#include <vector>
#include <SDL.h>

#include "EntityManager.h"
#include "Dispatcher.h"
#include "RenderingEngine.h"
#include "PhysicsEngine.h"
#include "InputProcessor.h"

#include "../Component/Player.h"
#include "../Component/Transform.h"
#include "../Component/Physics.h"
#include "../Component/Renderable.h"
#include "../Component/Sprite.h"
#include "../Component/Texture.h"

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
    EntityManager entityManager;
    Dispatcher dispatcher;
    PhysicsEngine physicsEngine;
    InputProcessor inputProcessor;
    RenderingEngine renderingEngine;

    SDL_Window* window;
    SDL_Event event{};
    bool isRunning;
    float deltaTime{};
};


#endif //BLOOM_ENGINE_CORE_H
