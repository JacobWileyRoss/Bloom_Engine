//
// Created by Jacob Ross on 3/25/24.
//

#ifndef BLOOM_ENGINE_ANIMATIONENGINE_H
#define BLOOM_ENGINE_ANIMATIONENGINE_H

#include <SDL.h>
#include <SDL_image.h>

#include "EntityManager.h"
#include "Dispatcher.h"
#include "Animation.h"
#include "Sprite.h"
#include "Texture.h"


class AnimationEngine {
    public:
    explicit AnimationEngine(EntityManager& entityManager, Dispatcher& dispatcher, float& deltaTime) :
                                entityManager(entityManager), dispatcher(dispatcher), deltaTime(deltaTime) {} ;

    void addFrame(int entityUID, AnimationType animationType, SDL_Texture *frame);
    std::vector<SDL_Texture*>& getAnimationType(int entityUID, AnimationType animationType);
    void handleInputEvent(const Event& event);
    void handleCollisionEvent(const Event& event);
    void startAnimation(int entityUID, AnimationType animationType);
    void stopAnimation(int entityUID, AnimationType animationType);
    void update(float deltaTime);

private:
    EntityManager& entityManager;
    Dispatcher& dispatcher;
    static SDL_Renderer* renderer;
    float& deltaTime;

};


#endif //BLOOM_ENGINE_ANIMATIONENGINE_H
