//
// Created by Jacob Ross on 3/25/24.
//

#ifndef BLOOM_ENGINE_ANIMATION_H
#define BLOOM_ENGINE_ANIMATION_H

#include "Component.h"
#include <vector>
#include <map>
#include <SDL.h>
#include <SDL_image.h>

enum class AnimationType {
    WalkCycleUP,
    WalkCycleDOWN,
    WalkCycleLEFT,
    WalkCycleRIGHT
};

// Converts the AnimationType enum to a string output (mainly for debugging)
inline std::string animationTypeToString(AnimationType type) {
    switch (type) {
        case AnimationType::WalkCycleUP: return "WalkCycleUp";
        case AnimationType::WalkCycleDOWN: return "WalkCycleDOWN";
        case AnimationType::WalkCycleLEFT: return "WalkCycleLEFT";
        case AnimationType::WalkCycleRIGHT: return "WalkCycleRIGHT";
        default: return "Unknown";
    }
}

class Animation : public Component {
public:
    // Animation cycles are stored as individual frames in a vector per animation cycle type
    std::vector<SDL_Texture*> walkCycleUP;
    std::vector<SDL_Texture*> walkCycleDOWN;
    std::vector<SDL_Texture*> walkCycleLEFT;
    std::vector<SDL_Texture*> walkCycleRIGHT;
    // Map of animations by type, each with their vector of frames
    std::map<AnimationType, std::vector<SDL_Texture*>> animations;
    bool isPlaying = false; // Add a flag to indicate if the animation is playing
    AnimationType currentAnimationType = AnimationType::WalkCycleDOWN; // Default or initial animation
    int currentFrameIndex = 0; // The index of the current frame to be displayed
    // TODO frameDuration should be set by Lua script and not hard coded here
    float frameDuration = 0.50; // Duration each frame is displayed
    float elapsedTime = 0; // Time elapsed since the current frame was shown


};

#endif //BLOOM_ENGINE_ANIMATION_H
