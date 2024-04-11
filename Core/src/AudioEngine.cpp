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

    // Load the strings bank
    FMOD_RESULT loadStringsBank = system->loadBankFile("../Game/assets/audio/Desktop/Master.strings.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &stringsBank);
    if (loadStringsBank != FMOD_OK) {
    std::cerr << "Failed to load master.strings bank: " << FMOD_ErrorString(result) << std::endl;
    return false;
    }
    std::cout << "[INFO] Master.Strings.Bank loaded from file successfully" << std::endl;
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
}
void AudioEngine::Update() {
    system->update(); // Just update the FMOD system
}

void AudioEngine::HandleInputEvent(const SDL_Event& event) {
    std::cout << "[INFO] AudioEngine::HandleInputEvent() called" << std::endl;
    PlayEvent("event:/Walking");
}

AudioEngine::~AudioEngine() {

}
