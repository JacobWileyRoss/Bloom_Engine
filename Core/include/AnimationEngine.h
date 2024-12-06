//
// Created by Jacob Ross on 3/25/24.
//

#ifndef BLOOM_ENGINE_ANIMATIONENGINE_H
#define BLOOM_ENGINE_ANIMATIONENGINE_H

//#include <SDL.h>
#include "../../../vendor/sdl2/2.30.1/include/SDL2/SDL.h"
#include "../../../vendor/sdl2_image/2.8.2_1/include/SDL2/SDL_image.h"
//#include <SDL_image.h>

#include "EntityManager.h"
#include "InputProcessor.h"
#include "Dispatcher.h"
#include "Animation.h"
#include "Sprite.h"
#include "Texture.h"


class AnimationEngine {
    public:
    explicit AnimationEngine(EntityManager& entityManager, InputProcessor& inputProcessor, Dispatcher& dispatcher, float& deltaTime) :
                                entityManager(entityManager), inputProcessor(inputProcessor), dispatcher(dispatcher), deltaTime(deltaTime) {} ;

    void addFrame(int entityUID, AnimationType animationType, SDL_Texture *frame);
    std::vector<SDL_Texture*>& getAnimationType(int entityUID, AnimationType animationType);
    void handleInputEvent(const Event& event);
    void handleCollisionEvent(const Event& event);
    void startAnimation(int entityUID, AnimationType animationType);
    void stopAnimation(int entityUID, AnimationType animationType);
    void update(float deltaTime);

private:
    EntityManager& entityManager;
    InputProcessor& inputProcessor;
    Dispatcher& dispatcher;
    static SDL_Renderer* renderer;
    float& deltaTime;

};


#endif //BLOOM_ENGINE_ANIMATIONENGINE_H
