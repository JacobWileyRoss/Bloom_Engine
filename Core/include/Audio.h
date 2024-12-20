//
// Created by Jacob Ross on 4/11/24.
//

#ifndef BLOOM_ENGINE_AUDIO_H
#define BLOOM_ENGINE_AUDIO_H

#include "Component.h"
#include <../../vendor/fmod/api/studio/inc/fmod_studio.hpp>

class Audio : public Component {
public:
std::string bankPath{""};
std::unordered_map<std::string, FMOD::Studio::EventInstance*> eventInstances;

~Audio() {
    eventInstances.clear();
}


};
#endif //BLOOM_ENGINE_AUDIO_H
