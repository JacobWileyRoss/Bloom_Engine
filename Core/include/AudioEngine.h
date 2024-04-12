//
// Created by Jacob Ross on 4/9/24.
//

#ifndef BLOOM_ENGINE_AUDIOENGINE_H
#define BLOOM_ENGINE_AUDIOENGINE_H

#include <iostream>

#include "EntityManager.h"
#include "Event.h"
#include "Audio.h"

#include <../../../vendor/fmod/api/core/inc/fmod.h>
#include <../../../vendor/fmod/api/core/inc/fmod.hpp>
#include <../../../vendor/fmod/api/core/inc/fmod_codec.h>
#include <../../../vendor/fmod/api/core/inc/fmod_common.h>
#include <../../../vendor/fmod/api/core/inc/fmod_errors.h>
#include "../../../vendor/fmod/api/studio/inc/fmod_studio.h"
#include "../../../vendor/fmod/api/studio/inc/fmod_studio.hpp"
#include "../../../vendor/fmod/api/studio/inc/fmod_studio_common.h"
#include "../../../vendor/fmod/api/fsbank/inc/fsbank.h"
#include "../../../vendor/fmod/api/fsbank/inc/fsbank_errors.h"

#include <../../../vendor/sdl2/2.30.1/include/SDL2/SDL_events.h>



class AudioEngine {
public:
    AudioEngine(EntityManager& entityManager);
    bool Initialize();
    void SetBank(int entityUID, std::string bankPath);
    void LoadBank(const std::string& bankPath);
    void LoadEntityBank(int entityUID);
    void PlayEvent(const std::string& eventPath);
    void PlayEvent(int entityUID, const std::string& eventPath);
    void Update();
    void HandleInputEvent(const Event& event);

    ~AudioEngine();

private:
    EntityManager& entityManager;
    FMOD::Studio::System* system = nullptr;
    FMOD::System* coreSystem;
    FMOD::Sound* sound = nullptr;
    FMOD::Channel* channel = nullptr;
    FMOD::Studio::Bank* masterBank = nullptr;
    FMOD::Studio::Bank* stringsBank = nullptr;


    };


#endif //BLOOM_ENGINE_AUDIOENGINE_H
