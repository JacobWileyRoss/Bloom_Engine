//
// Created by Jacob Ross on 4/9/24.
//

#include "../include/AudioEngine.h"

AudioEngine::AudioEngine() {}


bool AudioEngine::Initialize() {
    FMOD_RESULT result = FMOD::Studio::System::create(&system);
    if (result != FMOD_OK) {
        std::cerr << "Failed to create FMOD Studio System: " << FMOD_ErrorString(result) << std::endl;
        return false;
    }

    result = system->initialize(512, FMOD_STUDIO_INIT_LIVEUPDATE, FMOD_INIT_PROFILE_ENABLE, nullptr);
    if (result != FMOD_OK) {
        std::cerr << "Failed to initialize FMOD Studio System: " << FMOD_ErrorString(result) << std::endl;
        return false;
    }

    result = system->getCoreSystem(&coreSystem);
    if (result != FMOD_OK) {
        std::cerr << "Failed to get FMOD Core System: " << FMOD_ErrorString(result) << std::endl;
        return false;
    }

    FMOD::Debug_Initialize(FMOD_DEBUG_LEVEL_WARNING | FMOD_DEBUG_LEVEL_ERROR | FMOD_DEBUG_TYPE_FILE, FMOD_DEBUG_MODE_CALLBACK, nullptr, "fmod_log.txt");


    // Load the master bank
    FMOD_RESULT loadMasterBank = system->loadBankFile("../Game/assets/audio/Desktop/Master.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &masterBank);
    if (loadMasterBank != FMOD_OK) {
        std::cerr << "Failed to load master bank: " << FMOD_ErrorString(result) << std::endl;
        return false;
    }
    std::cout << "[INFO] MasterBank loaded from file successfully" << std::endl;
    PlayEvent("event:/Startup");
    return true;
}

void AudioEngine::LoadBank(const std::string& bankName) {
    std::cout << "Loading Bank: " << bankName << std::endl;
    FMOD_RESULT result = system->loadBankFile(bankName.c_str(), FMOD_STUDIO_LOAD_BANK_NORMAL, &masterBank);
    if (result != FMOD_OK) {
        std::cerr << "Failed to load bank: " << FMOD_ErrorString(result) << std::endl;
    }
    std::cout << "Bank loaded successfully" << std::endl;

}

void AudioEngine::PlayEvent(const std::string& eventPath) {
    FMOD::Studio::EventDescription* eventDescription = nullptr;
    FMOD_RESULT result = system->getEvent(eventPath.c_str(), &eventDescription);

    if (result != FMOD_OK) {
        std::cerr << "Error: Failed to get event description for " << eventPath
                  << ". Error: " << FMOD_ErrorString(result) << std::endl;
        return;
    }

    FMOD::Studio::EventInstance* eventInstance = nullptr;
    result = eventDescription->createInstance(&eventInstance);

    if (result != FMOD_OK) {
        std::cerr << "Error: Failed to create event instance for " << eventPath
                  << ". Error: " << FMOD_ErrorString(result) << std::endl;
        return;
    }

    result = eventInstance->start();

    if (result != FMOD_OK) {
        std::cerr << "Error: Failed to start event " << eventPath
                  << ". Error: " << FMOD_ErrorString(result) << std::endl;
        return;
    }

    // Optional: store eventInstance for further control, like stopping the event
    // Remember to release event instances when they are no longer needed
}




void AudioEngine::Update() {
    system->update(); // Just update the FMOD system
}

void AudioEngine::HandleInputEvent(const SDL_Event& event) {
    std::cout << "[INFO] AudioEngine::HandleInputEvent() called" << std::endl;
    PlayEvent("event:/Walking");
//    FMOD::Sound* sound = nullptr;
//    FMOD::Channel* channel = nullptr;
//    coreSystem->createSound("../Editor/assets/Startup.wav", FMOD_DEFAULT, 0, &sound);
//    coreSystem->playSound(sound, 0, false, &channel);
}








AudioEngine::~AudioEngine() {

}
