//
// Created by Jacob Ross on 3/25/24.
//

#include "../../include/System/AnimationEngine.h"

void AnimationEngine::addFrame(int entityUID, AnimationType animationType, SDL_Texture* frame) {
    auto& animation = entityManager.getEntityComponent<Animation>(entityUID, ComponentTypes::Animation);
    animation.animations[animationType].push_back(frame);
}

std::vector<SDL_Texture *>& AnimationEngine::getAnimationType(int entityUID, AnimationType animationType) {
    auto& entityAnimations = entityManager.getEntityComponent<Animation>
                                    (entityUID, ComponentTypes::Animation);
    // Static local vector used for the default case
    static std::vector<SDL_Texture*> emptyAnimation;
    switch (animationType) {
        case AnimationType::WalkCycleUP:
            return entityAnimations.walkCycleUP;
            break;
        case AnimationType::WalkCycleDOWN:
            return entityAnimations.walkCycleDOWN;
            break;
        case AnimationType::WalkCycleLEFT:
            return entityAnimations.walkCycleLEFT;
            break;
        case AnimationType::WalkCycleRIGHT:
            return entityAnimations.walkCycleRIGHT;
            break;
        default:
            std::cout << "[WARNING] AnimationType not handled" << std::endl;
            return emptyAnimation;
            break;
    }
}

void AnimationEngine::handleInputEvent(const Event& event) {
    std::cout << "[INFO] AnimationEngine received input event from Entity: " << event.entityUID << std::endl;

    // Attempt to get the SDL_Scancode from eventData
    auto scancode = std::get_if<SDL_Scancode>(&event.eventData);
    if (scancode) { // Check if scancode was successfully obtained
        switch (*scancode) {
            case SDL_SCANCODE_W:
                std::cout << "[INFO] AnimationEngine detected W Key Event" << std::endl;
                if (event.eventType == EventType::InputKeyDown) {
                    startAnimation(event.entityUID, AnimationType::WalkCycleUP);
                } else if (event.eventType == EventType::InputKeyUp) {
                    stopAnimation(event.entityUID, AnimationType::WalkCycleUP);
                }
                break;
            case SDL_SCANCODE_S:
                std::cout << "[INFO] AnimationEngine detected S Key Event" << std::endl;
                if (event.eventType == EventType::InputKeyDown) {
                    startAnimation(event.entityUID, AnimationType::WalkCycleDOWN);
                } else if (event.eventType == EventType::InputKeyUp) {
                    stopAnimation(event.entityUID, AnimationType::WalkCycleDOWN);
                }
                break;
            case SDL_SCANCODE_A:
                std::cout << "[INFO] AnimationEngine detected A Key Event" << std::endl;
                if (event.eventType == EventType::InputKeyDown) {
                    startAnimation(event.entityUID, AnimationType::WalkCycleLEFT);
                } else if (event.eventType == EventType::InputKeyUp) {
                    stopAnimation(event.entityUID, AnimationType::WalkCycleLEFT);
                }
                break;
            case SDL_SCANCODE_D:
                std::cout << "[INFO] AnimationEngine detected D Key Event" << std::endl;
                if (event.eventType == EventType::InputKeyDown) {
                    startAnimation(event.entityUID, AnimationType::WalkCycleRIGHT);
                } else if (event.eventType == EventType::InputKeyUp) {
                    stopAnimation(event.entityUID, AnimationType::WalkCycleRIGHT);
                }
                break;
            default:
                std::cout << "[WARNING] SDL_Scancode type not handled by AnimationEngine" << std::endl;
                break;
        }
    }
}


void AnimationEngine::startAnimation(int entityUID, AnimationType animationType) {
    auto& animationComponent = entityManager.getEntityComponent<Animation>(entityUID, ComponentTypes::Animation);
    // Set the current animation type
    animationComponent.currentAnimationType = animationType;
    // Reset the frame index and elapsed time to start the animation from the beginning
    animationComponent.currentFrameIndex = 0;
    animationComponent.elapsedTime = 0.0f;
    // Set the animation to play
    animationComponent.isPlaying = true;
    std::cout << "[INFO] isPlaying is set to: " << animationComponent.isPlaying << std::endl;
    std::cout << "[INFO] Starting animation for entity " << entityUID << " type: " << animationTypeToString(animationType) << std::endl;
}

void AnimationEngine::stopAnimation(int entityUID, AnimationType animationType) {
    auto& animationComponent = entityManager.getEntityComponent<Animation>(entityUID, ComponentTypes::Animation);
    if(animationComponent.currentAnimationType == animationType) {
        animationComponent.isPlaying = false;
        animationComponent.currentFrameIndex = 0; // Reset to the first frame
        std::cout << "[INFO] Stopping animation for entity " << entityUID << " type: " << animationTypeToString(animationType) << std::endl;
    } else {
        std::cout << "[WARNING] Attempted to stop an animation that is not currently playing for entity " << entityUID << std::endl;
    }
}


void AnimationEngine::update(float deltaTime) {
    for (auto& [entityUID, entity] : entityManager.entities) {
        if (entityManager.hasComponent(entityUID, ComponentTypes::Animation)) {
            auto& animation = entityManager.getEntityComponent<Animation>(entityUID, ComponentTypes::Animation);

            // Ensure animation is playing and has a non-zero frameDuration
            if (animation.isPlaying && animation.frameDuration > 0.0f && !animation.animations[animation.currentAnimationType].empty()) {
                animation.elapsedTime += deltaTime;

                // Calculate the number of frames to advance
                int frameAdvances = static_cast<int>(animation.elapsedTime / animation.frameDuration);
                animation.elapsedTime -= frameAdvances * animation.frameDuration;
                animation.currentFrameIndex = (animation.currentFrameIndex + frameAdvances) % animation.animations[animation.currentAnimationType].size();

                // Update the texture component with the new frame
                if (entityManager.hasComponent(entityUID, ComponentTypes::Texture)) {
                    auto& textureComponent = entityManager.getEntityComponent<Texture>(entityUID, ComponentTypes::Texture);
                    textureComponent.texture = animation.animations[animation.currentAnimationType][animation.currentFrameIndex];
                }
            }
        }
    }
}
