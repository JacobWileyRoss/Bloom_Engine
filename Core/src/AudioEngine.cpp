//
// Created by Jacob Ross on 4/9/24.
//

#include "../include/AudioEngine.h"

AudioEngine::AudioEngine() {}

bool AudioEngine::Initialize() {
    FMOD_RESULT result = FMOD::System_Create(&system);
    if (result != FMOD_OK) {
        std::cerr << "Failed to create FMOD system: " << FMOD_ErrorString(result) << std::endl;
        return false;
    }

    result = system->init(512, FMOD_INIT_NORMAL, 0);
    if (result != FMOD_OK) {
        std::cerr << "Failed to initialize FMOD system: " << FMOD_ErrorString(result) << std::endl;
        return false;
    }

    std::cout << "[INFO] FMOD initialized successfully." << std::endl;
    return true;
}

void AudioEngine::Play(const char* filepath) {
    std::cout << "[INFO] Preparing to play sound." << std::endl;

    FMOD_RESULT result = system->createSound(filepath, FMOD_DEFAULT, 0, &sound);
    if (result != FMOD_OK) {
        std::cerr << "Failed to create sound: " << FMOD_ErrorString(result) << std::endl;
        return;
    }

    result = system->playSound(sound, nullptr, false, &channel);
    if (result != FMOD_OK) {
        std::cerr << "Failed to play sound: " << FMOD_ErrorString(result) << std::endl;
        return;
    }

    std::cout << "[INFO] Sound is playing." << std::endl;
}

void AudioEngine::Update() {
    system->update(); // Just update the FMOD system
}

void AudioEngine::HandleInputEvent(const SDL_Event& event) {
    if (event.type == SDL_KEYDOWN && !event.key.repeat) { // Check for key down without repeat
        StartSound("../Game/assets/audio/sfx_step_sand_l.flac");
    } else if (event.type == SDL_KEYUP) {
        StopSound();
    }
}


bool AudioEngine::isChannelPlaying() {
    if (!channel) {
        return false; // No channel to check, so it's not playing
    }

    bool playing = false;
    FMOD_RESULT result = channel->isPlaying(&playing);
    if (result != FMOD_OK) {
        std::cerr << "Failed to check if channel is playing: " << FMOD_ErrorString(result) << std::endl;
        return false; // Treat any error as not playing
    }

    return playing;
}

void AudioEngine::StartSound(const char* filepath) {
    if (!isPlaying) {
        if (sound) { // Check if there's a previous sound and release it
            sound->release();
            sound = nullptr; // Nullify the sound object
        }

        FMOD_RESULT result = system->createSound(filepath, FMOD_DEFAULT, 0, &sound);
        if (result != FMOD_OK) {
            std::cerr << "Failed to create sound: " << FMOD_ErrorString(result) << std::endl;
            return;
        }

        result = system->playSound(sound, nullptr, false, &channel);
        if (result != FMOD_OK) {
            std::cerr << "Failed to play sound: " << FMOD_ErrorString(result) << std::endl;
            sound->release(); // Release the sound if it fails to play
            sound = nullptr; // Nullify the sound object
            return;
        }

        isPlaying = true;
    }
}

void AudioEngine::StopSound() {
    if (isPlaying && channel) {
        channel->stop();
        sound->release(); // Release the sound to properly free resources
        sound = nullptr; // Nullify the sound object
        isPlaying = false;
    }
}



AudioEngine::~AudioEngine() {
    if (sound) {
        sound->release();
    }
    if (system) {
        system->close();
        system->release();
    }
}