//
// Created by Jacob Ross on 3/24/24.
//

#include "../include/EntityManager.h"
EntityManager::EntityManager() {
    std::cout << "[INFO] EntityManager Created!" << std::endl;
}

// TODO Attaches Transform Component by default so other component types don't crash if attached first needs a better fix
int EntityManager::createEntity() {
    int entityUID = nextUID++;
    entities.emplace(entityUID, Entity(entityUID));
    attachComponent(entityUID, ComponentType::Transform);
    std::cout << "[INFO] Entity " << entityUID << " created successfully" << std::endl;
    return entityUID;
}

void EntityManager::destroyEntity(int entityUID) {
    entities.erase(entityUID);
    std::cout << "[INFO] Destroyed Entity: " << entityUID << std::endl;
    nextUID -=1;
}

// TODO Needs better error handling
bool EntityManager::hasComponent(int entityUID, const ComponentType& componentType) {
    auto entityIt = entities.find(entityUID);
    if (entityIt != entities.end()) {
        // Check if the entity has the specified component type
        const auto& components = entityIt->second.components;
        return components.find(componentType) != components.end();
    }
    return false; // Entity not found or does not have the component
}

std::unique_ptr<Component> EntityManager::createComponent(ComponentType componentType) {
    switch (componentType) {
        case ComponentType::Animation:
            return std::make_unique<Animation>();
        case ComponentType::Audio:
            std::cout << "[DEBUG] Attaching Audio component" << std::endl;
            return std::make_unique<Audio>();
        case ComponentType::Camera:
            return std::make_unique<Camera>();
        case ComponentType::Collider:
            return std::make_unique<Collider>();
        case ComponentType::Event:
            return std::make_unique<Event>();
        case ComponentType::Physics:
            return std::make_unique<Physics>();
        case ComponentType::Player:
            return std::make_unique<Player>();
        case ComponentType::Renderable:
            return std::make_unique<Renderable>();
        case ComponentType::Sprite:
            return std::make_unique<Sprite>();
        case ComponentType::Transform:
            return std::make_unique<Transform>();
        case ComponentType::Texture:
            return std::make_unique<Texture>();
    }
}

void EntityManager::attachComponent(int entityUID, ComponentType componentType) {
    auto entity = entities.find(entityUID);
    if (entity != entities.end()) {
        std::unique_ptr<Component> component = createComponent(componentType);
        if (component) {
            entity->second.components.emplace(componentType, std::move(component));
            std::cout <<  "[INFO] " << componentTypeToString(componentType) <<
            " component attached to Entity: " << entityUID << std::endl;
        }
    } else {
        std::cerr << "Entity with UID " << entityUID << " not found!" << std::endl;
    }
}

void EntityManager::removeComponent(int entityUID, ComponentType componentType) {
    auto entityIt = entities.find(entityUID);
    if (entityIt != entities.end()) {
        auto& components = entityIt->second.components;
        auto compIt = components.find(componentType);
        if (compIt != components.end()) {
            components.erase(compIt);
            std::cout << "[INFO] " << componentTypeToString(componentType) << " component removed from Entity: " << entityUID << std::endl;
        } else {
            std::cerr << "[ERROR] Component not found in Entity: " << entityUID << std::endl;
        }
    } else {
        std::cerr << "[ERROR] Entity not found: " << entityUID << std::endl;
    }
}

// TODO Should function return a pointer instead of a reference? This allows for better error handling if the entityUID is not found (Update Doxygen if changed)
Entity& EntityManager::getEntity(int entityUID) {
    auto entity = entities.find(entityUID);
    return entity->second;
}

