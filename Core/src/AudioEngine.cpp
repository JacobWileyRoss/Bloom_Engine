//
// Created by Jacob Ross on 4/9/24.
//

#include "../include/AudioEngine.h"

AudioEngine::AudioEngine(EntityManager& entityManager) : entityManager(entityManager) {}

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
    loadedBanks.push_back(masterBank);
    std::cout << "[INFO] MasterBank loaded from file successfully" << std::endl;

    // Load the strings bank
    FMOD_RESULT loadStringsBank = system->loadBankFile("../Game/assets/audio/Desktop/Master.strings.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &stringsBank);
    if (loadStringsBank != FMOD_OK) {
    std::cerr << "Failed to load master.strings bank: " << FMOD_ErrorString(result) << std::endl;
    return false;
    }
    std::cout << "[INFO] Master.Strings.Bank loaded from file successfully" << std::endl;
    loadedBanks.push_back(stringsBank);
    return true;
}

void AudioEngine::SetBank(int entityUID, std::string bankPath) {

    if (entityManager.hasComponent(entityUID, ComponentType::Audio)) {
        auto& audio = entityManager.getEntityComponent<Audio>(entityUID, ComponentType::Audio);
        audio.bankPath = bankPath;
        std::cout << "[INFO] Bank set successfully for Entity: " << entityUID << std::endl;
    } else {
        std::cerr << "Error: No Audio component found for Entity: " << entityUID << std::endl;
    }
}

std::string AudioEngine::getEntityBank(int entityUID) {
    auto& audio = entityManager.getEntityComponent<Audio>(entityUID, ComponentType::Audio);
    return audio.bankPath;
}


bool AudioEngine::LoadBank(const std::string& bankPath) {
    std::cout << "Loading Bank: " << bankPath << std::endl;
    FMOD::Studio::Bank* bank = nullptr;
    FMOD_RESULT result = system->loadBankFile(bankPath.c_str(), FMOD_STUDIO_LOAD_BANK_NORMAL, &bank);
    if (result != FMOD_OK) {
        std::cerr << "Failed to load bank: " << FMOD_ErrorString(result) << std::endl;
        return false;
    }
    loadedBanks.push_back(bank);
    std::cout << "Bank at " << bankPath << "loaded successfully" << std::endl;
    return true;
}

void AudioEngine::LoadEntityBank(int entityUID) {
    std::cout << "[INFO] Loading Bank for Entity: " << entityUID << std::endl;
    FMOD::Studio::Bank* bank = nullptr;
    auto& audio = entityManager.getEntityComponent<Audio>(entityUID, ComponentType::Audio);
    FMOD_RESULT result = system->loadBankFile(audio.bankPath.c_str(), FMOD_STUDIO_LOAD_BANK_NORMAL, &bank);
    if (result != FMOD_OK) {
        std::cerr << "[ERROR] Failed to load bank: " << FMOD_ErrorString(result) << std::endl;
    }
    loadedBanks.push_back(bank);
    std::cout << "[INFO] Bank loaded successfully" << std::endl;
}

void AudioEngine::UnloadBank(FMOD::Studio::Bank* bank) {
    bank->unload();
}

void AudioEngine::UnloadAllBanks() {
    for(auto bank : loadedBanks) {
        bank->unload();
    }
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
    activeEvents.emplace(eventPath, eventInstance);
    std::cout << "[INFO] AudioEngine::PlayEvent(" << eventPath << ")" << std::endl;
}

FMOD::Studio::EventInstance* AudioEngine::PlayEvent(int entityUID, const std::string& eventName, const std::string& eventPath) {
    auto& audioComponent = entityManager.getEntityComponent<Audio>(entityUID, ComponentType::Audio);

    FMOD::Studio::EventDescription* eventDescription = nullptr;
    FMOD_RESULT result = system->getEvent(eventPath.c_str(), &eventDescription);

    if (result != FMOD_OK) {
    std::cerr << "Error: Failed to get event description for " << eventPath
    << ". Error: " << FMOD_ErrorString(result) << std::endl;
    }

    if (audioComponent.eventInstances.count(eventName) > 0) {
        FMOD::Studio::EventInstance* oldEvent = audioComponent.eventInstances[eventName];
        if (oldEvent) {
            oldEvent->stop(FMOD_STUDIO_STOP_IMMEDIATE);
            oldEvent->release();
        }
    }

    FMOD::Studio::EventInstance* eventInstance = nullptr;
    result = eventDescription->createInstance(&eventInstance);
    if (result != FMOD_OK) {
        std::cerr << "Error: Failed to create event instance for " << eventPath
        << ". Error: " << FMOD_ErrorString(result) << std::endl;
    }

    result = eventInstance->start();
    if (result != FMOD_OK) {
        std::cerr << "Error: Failed to start event " << eventPath
        << ". Error: " << FMOD_ErrorString(result) << std::endl;
    }

    audioComponent.eventInstances[eventName] = eventInstance;
    std::cout << "[INFO] AudioEngine::PlayEvent(" << eventName << ", " << eventPath << ")" << std::endl;
    activeEvents.emplace(eventPath, eventInstance);
    return eventInstance;
}

void AudioEngine::Update() {
    system->update(); // Just update the FMOD system
}

void AudioEngine::HandleInputEvent(const Event& event) {
    std::cout << "[INFO] AudioEngine::HandleInputEvent() called" << std::endl;

    if(event.eventType == EventType::InputKeyDown) {
    auto eventInstance = PlayEvent(event.entityUID, "walking", "event:/Walking");
    eventInstance->setParameterByName("repeat", 1.0);
    }
    if(event.eventType == EventType::InputKeyUp) {
        std::cout << "[DEBUG] HandleInputEvent() InputKeyUp called" << std::endl;
        auto& audioComponent = entityManager.getEntityComponent<Audio>(event.entityUID, ComponentType::Audio);
        if (audioComponent.eventInstances.count("walking") > 0) {
            FMOD::Studio::EventInstance* eventInstance = audioComponent.eventInstances["walking"];
            eventInstance->stop(FMOD_STUDIO_STOP_IMMEDIATE);
            eventInstance->release();
            audioComponent.eventInstances.erase("walking");
        }
    }
}

void AudioEngine::StopAllActiveEvents() {
    std::cout << "[INFO] AudioEngine::StopAllActiveEvents() called" << std::endl;
    for (auto& eventPair : activeEvents) {
        FMOD::Studio::EventInstance* eventInstance = eventPair.second;
        if (eventInstance) {
            eventInstance->stop(FMOD_STUDIO_STOP_IMMEDIATE);
            eventInstance->release();
        }
    }
    activeEvents.clear();
    std::cout << "[INFO] All audio events have been stopped and released." << std::endl;
}

AudioEngine::~AudioEngine() {

}
