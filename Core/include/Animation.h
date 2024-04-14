//
// Created by Jacob Ross on 3/25/24.
//

/**
 * @file Animation.h
 * @brief Animation component
 *
 * The Animation component tells the AnimationEngine that an entity contains animation data. It stores the frames
 * associated with animation cycles, and it stores each animation cycle itself.
 */

#ifndef BLOOM_ENGINE_ANIMATION_H
#define BLOOM_ENGINE_ANIMATION_H

#include "Component.h"
#include <vector>
#include <map>
#include "../../../vendor/sdl2/2.30.1/include/SDL2/SDL.h"
#include "../../../vendor/sdl2_image/2.8.2_1/include/SDL2/SDL_image.h"

/**
 * @brief AnimationType stores each TYPE of animation cycle available, NOT the animation itself (frame data)
 */
enum class AnimationType {
    // TODO ScriptingEngine should be able to add and remove from AnimationType to decouple animators from the engine
    WalkCycleUP,
    WalkCycleDOWN,
    WalkCycleLEFT,
    WalkCycleRIGHT
};

/**
 * @brief Converts the AnimationType enum to a string output (mainly for debugging)
 * @param type is a specified type from AnimationType enum
 * @return Returns a string equivalent of the specified AnimationType
 */
inline std::string animationTypeToString(AnimationType type) {
    switch (type) {
        case AnimationType::WalkCycleUP: return "WalkCycleUp";
        case AnimationType::WalkCycleDOWN: return "WalkCycleDOWN";
        case AnimationType::WalkCycleLEFT: return "WalkCycleLEFT";
        case AnimationType::WalkCycleRIGHT: return "WalkCycleRIGHT";
        default: return "Unknown";
    }
}

/**
 * @class Animation
 * @brief Animation component class that inherits from the Component base class
 */
class Animation : public Component {
public:
    // Animation cycles are stored as individual frames in a vector per animation cycle type
    // TODO AnimationEngine should be able to add/remove SDL_Texture vectors to decouple animators from engine
    std::vector<SDL_Texture*> walkCycleUP; ///< Vector that contains SDL_Texture*'s for the walk cycle up
    std::vector<SDL_Texture*> walkCycleDOWN; ///< Vector that contains SDL_Texture*'s for the walk cycle down
    std::vector<SDL_Texture*> walkCycleLEFT; ///< Vector that contains SDL_Texture*'s for the walk cycle left
    std::vector<SDL_Texture*> walkCycleRIGHT; ///< Vector that contains SDL_Texture*'s for the walk cycle right
    std::map<AnimationType, std::vector<SDL_Texture*>> animations; ///< Map that stores the animation cycle vector associated with the AnimationType key
    bool isPlaying = false; ///< Boolean value set to whether an animation is playing or not
    AnimationType currentAnimationType = AnimationType::WalkCycleDOWN; ///< Stores the currently selected/playing AnimationType. Default set to walk down
    int currentFrameIndex = 0; ///< Stores the current animation frame index position
    // TODO frameDuration should be set by Lua script and not hard coded here
    float frameDuration = 0.06; ///< Duration each frame is displayed
    float elapsedTime = 0; ///< Time elapsed since the current frame was shown
};

#endif //BLOOM_ENGINE_ANIMATION_H
