//
// Created by Jacob Ross on 3/25/24.
//

#include "../include/AnimationEngine.h"

// This function accepts a SDL-Texture* that represents an individual frame and the AnimationType that it corresponds
// to. The frame is then added into the appropriate vector to store all frames in an AnimationType
void AnimationEngine::addFrame(int entityUID, AnimationType animationType, SDL_Texture* frame) {
    std::cout << "[DEBUG] AnimationEngine::addFrame() called successfully" << std::endl;
    auto& animation = entityManager.getEntityComponent<Animation>
            (entityUID, ComponentType::Animation);
    std::cout << "[DEBUG] AnimationEngine getEntityComponent called successfully" << std::endl;

    animation.animations[animationType].push_back(frame);
    std::cout << "[Info] Added frame to: " << animationTypeToString(animationType) << std::endl;
}

// This function is used to return the actual vector that stores animation frames for specified AnimationType
std::vector<SDL_Texture *>& AnimationEngine::getAnimationType(int entityUID, AnimationType animationType) {
    auto& entityAnimations = entityManager.getEntityComponent<Animation>
                                    (entityUID, ComponentType::Animation);
    // Static empty local vector used for the default case
    static std::vector<SDL_Texture*> emptyAnimation;
    switch (animationType) {
        case AnimationType::WalkCycleUP:
            return entityAnimations.walkCycleUP;
        case AnimationType::WalkCycleDOWN:
            return entityAnimations.walkCycleDOWN;
        case AnimationType::WalkCycleLEFT:
            return entityAnimations.walkCycleLEFT;
        case AnimationType::WalkCycleRIGHT:
            return entityAnimations.walkCycleRIGHT;
        default:
            std::cout << "[WARNING] AnimationType not handled" << std::endl;
            return emptyAnimation;
    }
}

// This function checks the animationType, if it is different from the currentAnimationType it
// sets the new animationType and begins the animation cycle
void AnimationEngine::startAnimation(int entityUID, AnimationType animationType) {
    std::cout << "[DEBUG] startAnimation called for: " << animationTypeToString(animationType) << std::endl;
    auto& animationComponent = entityManager.getEntityComponent<Animation>(entityUID,
                                                                           ComponentType::Animation);

    // Set the current animation type
    animationComponent.currentAnimationType = animationType;

    // Reset the frame index and elapsed time to start the animation from the beginning
    animationComponent.currentFrameIndex = 0;
    animationComponent.elapsedTime = 0.0f;

    // Set the animation to play
    animationComponent.isPlaying = true;
    std::cout << "[INFO] isPlaying is set to: " << animationComponent.isPlaying << std::endl;
    std::cout << "[INFO] Starting animation for entity " << entityUID << " type: " <<
              animationTypeToString(animationType) << std::endl;
}

// This function checks pressedKeys to determine the most up-to-date animationType to playback. If there are
// no pressedKeys it halts all animation playback
void AnimationEngine::stopAnimation(int entityUID, AnimationType animationType) {
    auto& animation = entityManager.getEntityComponent<Animation>(entityUID,
                                                                           ComponentType::Animation);
    auto& pressedKeys = inputProcessor.getPressedKeys();
    if (!pressedKeys.empty()) {
        if (pressedKeys.find(KeyCode::W) != pressedKeys.end()) {
            startAnimation(entityUID, AnimationType::WalkCycleUP);
        } else if (pressedKeys.find(KeyCode::S) != pressedKeys.end()) {
            startAnimation(entityUID, AnimationType::WalkCycleDOWN);
        } else if (pressedKeys.find(KeyCode::A) != pressedKeys.end()) {
            startAnimation(entityUID, AnimationType::WalkCycleLEFT);
        } else if (pressedKeys.find(KeyCode::D) != pressedKeys.end()) {
            startAnimation(entityUID, AnimationType::WalkCycleRIGHT);
        }
    } else {
        if (animation.isPlaying) {
            std::cout << "[INFO] Stopping animation for entity " << entityUID << " type: " <<
                      animationTypeToString(animationType) << std::endl;
            animation.isPlaying = false;
            animation.currentFrameIndex = 0;
            auto& animationFrames = animation.animations[animation.currentAnimationType];
            if (!animationFrames.empty()) {
                if (entityManager.hasComponent(entityUID, ComponentType::Texture)) {
                    auto& textureComponent = entityManager.getEntityComponent<Texture>
                            (entityUID, ComponentType::Texture);
                    textureComponent.texture = animationFrames[0];
                }
            }
        } else {
            std::cout << "[WARNING] Attempted to stop an animation that is not currently playing for entity " <<
                      entityUID << std::endl;
        }
    }
}

// TODO I need to review the update() function and make sure I completely understand it and determine if its the best method
// This function updates the animation cycles using DeltaTime and the frameDuration that is currently defined in
// the actual Animation Component (which is a TODO)
void AnimationEngine::update(float deltaTime) {
    for (auto& [entityUID, entity] : entityManager.entities) {
        if (entityManager.hasComponent(entityUID, ComponentType::Animation)) {
            auto& animation = entityManager.getEntityComponent<Animation>(entityUID,
                                                                          ComponentType::Animation);
            auto& animationFrames = animation.animations[animation.currentAnimationType];

            // Ensure animation is playing and has a non-zero frameDuration
            if (animation.isPlaying && animation.frameDuration > 0.0f &&
            !animation.animations[animation.currentAnimationType].empty()) {
                animation.elapsedTime += deltaTime;

                // Calculate the number of frames to advance
                int frameAdvances = static_cast<int>(animation.elapsedTime / animation.frameDuration);
                animation.elapsedTime -= frameAdvances * animation.frameDuration;
                animation.currentFrameIndex = (animation.currentFrameIndex + frameAdvances) %
                        animation.animations[animation.currentAnimationType].size();

                // Update the texture component with the new frame
                if (entityManager.hasComponent(entityUID, ComponentType::Texture)) {
                    auto& textureComponent = entityManager.getEntityComponent<Texture>
                            (entityUID, ComponentType::Texture);
                    textureComponent.texture = animationFrames[animation.currentFrameIndex];
                }
            }
        }
    }
}
