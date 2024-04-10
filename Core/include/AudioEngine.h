//
// Created by Jacob Ross on 4/9/24.
//

#ifndef BLOOM_ENGINE_AUDIOENGINE_H
#define BLOOM_ENGINE_AUDIOENGINE_H

#include <iostream>

#include <../../../vendor/fmod/api/core/inc/fmod.h>
#include <../../../vendor/fmod/api/core/inc/fmod.hpp>
#include <../../../vendor/fmod/api/core/inc/fmod_codec.h>
#include <../../../vendor/fmod/api/core/inc/fmod_common.h>
#include <../../../vendor/fmod/api/core/inc/fmod_errors.h>

#include <../../../vendor/sdl2/2.30.1/include/SDL2/SDL_events.h>



class AudioEngine {
public:
    AudioEngine();
    bool Initialize();
    void StartSound(const char* filepath);
    void StopSound();
    void Update();
    void HandleInputEvent(const SDL_Event& event);
    bool isChannelPlaying();
    ~AudioEngine();

private:
    FMOD::System* system = nullptr;
    FMOD::Sound* sound = nullptr;
    FMOD::Channel* channel = nullptr;
    bool isPlaying;

};


#endif //BLOOM_ENGINE_AUDIOENGINE_H
