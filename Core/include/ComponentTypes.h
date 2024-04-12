//
// Created by Jacob Ross on 3/25/24.
//

#ifndef BLOOM_ENGINE_COMPONENTTYPES_H
#define BLOOM_ENGINE_COMPONENTTYPES_H

enum class ComponentTypes {
    Animation,
    Audio,
    Camera,
    Collider,
    Event,
    Physics,
    Player,
    Renderable,
    Sprite,
    Texture,
    Transform,
};

inline std::string componentTypeToString(ComponentTypes type) {
    switch (type) {
        case ComponentTypes::Animation: return "Animation";
        case ComponentTypes::Audio: return "Audio";
        case ComponentTypes::Camera: return "Camera";
        case ComponentTypes::Collider: return "Collider";
        case ComponentTypes::Event: return "Event";
        case ComponentTypes::Physics: return "Physics";
        case ComponentTypes::Player: return "Player";
        case ComponentTypes::Renderable: return "Renderable";
        case ComponentTypes::Sprite: return "Sprite";
        case ComponentTypes::Texture: return "Texture";
        case ComponentTypes::Transform: return "Transform";
        default: return "Unknown";
    }
}

#endif //BLOOM_ENGINE_COMPONENTTYPES_H
