//
// Created by Jacob Ross on 3/24/24.
//

#ifndef BLOOM_ENGINE_COMPONENT_H
#define BLOOM_ENGINE_COMPONENT_H

/**
 * @file Component
 * @brief Header file for Component
 * The Component serves as the base class for all components available in the engine.
 */

#include <iostream>

/**
 * @class ComponentType
 * @brief The ComponentType enum class stores all available Component types
 */
enum class ComponentType {
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

/**
 * @brief Gets the string equivalent output of specified ComponentType
 * @param type
 * @return Returns a string value of the specified ComponentType
 */
inline std::string componentTypeToString(ComponentType type) {
    switch (type) {
        case ComponentType::Animation: return "Animation";
        case ComponentType::Audio: return "Audio";
        case ComponentType::Camera: return "Camera";
        case ComponentType::Collider: return "Collider";
        case ComponentType::Event: return "Event";
        case ComponentType::Physics: return "Physics";
        case ComponentType::Player: return "Player";
        case ComponentType::Renderable: return "Renderable";
        case ComponentType::Sprite: return "Sprite";
        case ComponentType::Texture: return "Texture";
        case ComponentType::Transform: return "Transform";
        default: return "Unknown";
    }
}

/**
 * @class Component
 * @brief Base class for all components
 * The Component class serves as the base class for all available components in the engine. Contains a string value of
 * the ComponentType
 */
class Component {
public:
    Component(){}; ///< Component constructor

    // TODO I think the string type is redundant only need ComponentType and componentTypeToString
    std::string type; ///< Stores a string value of the ComponentType
    virtual ~Component() = default; ///< Component virtual Destructor

};


#endif //BLOOM_ENGINE_COMPONENT_H
