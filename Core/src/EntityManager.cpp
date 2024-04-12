//
// Created by Jacob Ross on 3/24/24.
//

#include "../include/EntityManager.h"
EntityManager::EntityManager() {
    std::cout << "[INFO] EntityManager Created!" << std::endl;
}

// This creates a new blank entity and returns the new entityUID
// It automatically attaches a Transform component as other component types will crash without the transform
int EntityManager::createEntity() {
    int entityUID = nextUID++;
    entities.emplace(entityUID, Entity(entityUID));
    attachComponent(entityUID, ComponentTypes::Transform);
    std::cout << "[INFO] Entity " << entityUID << " created successfully" << std::endl;
    return entityUID;
}

// Destroys entity object specified by the entityUID and removes it from the entities map container
void EntityManager::destroyEntity(int entityUID) {
    entities.erase(entityUID);
    std::cout << "[INFO] Destroyed Entity: " << entityUID << std::endl;
    nextUID -=1;
}

bool EntityManager::hasComponent(int entityUID, const ComponentTypes& componentType) {
    auto entityIt = entities.find(entityUID);
    if (entityIt != entities.end()) {
        // Check if the entity has the specified component type
        const auto& components = entityIt->second.components;
        return components.find(componentType) != components.end();
    }
    return false; // Entity not found or does not have the component
}

// Creates a component based on the componentType selection. This is used by attachComponent() for composing entities
std::unique_ptr<Component> EntityManager::createComponent(ComponentTypes componentType) {
    switch (componentType) {
        case ComponentTypes::Animation:
            return std::make_unique<Animation>();
        case ComponentTypes::Audio:
            std::cout << "[DEBUG] Attaching Audio component" << std::endl;
            return std::make_unique<Audio>();
        case ComponentTypes::Camera:
            return std::make_unique<Camera>();
        case ComponentTypes::Collider:
            return std::make_unique<Collider>();
        case ComponentTypes::Event:
            return std::make_unique<Event>();
        case ComponentTypes::Physics:
            return std::make_unique<Physics>();
        case ComponentTypes::Player:
            return std::make_unique<Player>();
        case ComponentTypes::Renderable:
            return std::make_unique<Renderable>();
        case ComponentTypes::Sprite:
            return std::make_unique<Sprite>();
        case ComponentTypes::Transform:
            return std::make_unique<Transform>();
        case ComponentTypes::Texture:
            return std::make_unique<Texture>();
    }
}

// Attaches a component determined by the componentType selection. This calls createComponent to create component
// type specified
void EntityManager::attachComponent(int entityUID, ComponentTypes componentType) {
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

// Remove specified component type
void EntityManager::removeComponent(int entityUID, ComponentTypes componentType) {
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

// Returns the actual entity object requested by the entityUID
Entity& EntityManager::getEntity(int entityUID) {
    auto entity = entities.find(entityUID);
    return entity->second;
}

