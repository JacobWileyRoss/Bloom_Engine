//
// Created by Jacob Ross on 3/24/24.
//

#ifndef BLOOM_ENGINE_RENDERINGENGINE_H
#define BLOOM_ENGINE_RENDERINGENGINE_H

#include <iostream>
#include <vector>
#include <memory>
#include "../../../vendor/sdl2/2.30.1/include/SDL2/SDL.h"
#include "EntityManager.h"
#include "Dispatcher.h"
#include "Transform.h"
#include "Renderable.h"
#include "Sprite.h"
#include "Texture.h"
#include "Camera.h"




class RenderingEngine {
public:
    explicit RenderingEngine(EntityManager& entityManager, Dispatcher& dispatcher) : entityManager(entityManager),
                                                                                     dispatcher(dispatcher){} ;

    static void Initialize(SDL_Window* window);
    void setSprite(int entityUID, float x, float y, float w, float h);
    void setTexture(int entityUID, std::string filename);
    void setCamera(int entityUID, int posX, int posY, int width, int height);
    void update(std::unordered_map<int, Entity>& entities);
    void Render(std::unordered_map<int, Entity>& entities);
    SDL_Renderer* GetRenderer() { return renderer; };
    SDL_Texture* GetRenderTargetTexture() const { return renderTargetTexture; }
    void setRenderLayer(int entityUID, RenderLayer renderLayer);
    bool hasCameraEntity() {return cameraEntity;}
    void Shutdown();

private:
    EntityManager& entityManager;
    Dispatcher& dispatcher;
    static SDL_Renderer* renderer;
    static SDL_Texture* renderTargetTexture;
    bool cameraEntity{false};

};

#endif //BLOOM_ENGINE_RENDERINGENGINE_H
