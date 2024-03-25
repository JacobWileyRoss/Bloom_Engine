//
// Created by Jacob Ross on 3/24/24.
//

#include "../../include/System/EntityManager.h"
EntityManager::EntityManager() {
    std::cout << "[INFO] EntityManager Created!" << std::endl;
}

int EntityManager::createEntity() {
    int entityUID = nextUID++;
    entities.emplace(entityUID, Entity(entityUID));
    std::cout << "[INFO] Entity " << entityUID << " created successfully" << std::endl;
    return entityUID;
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
// object requested
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

Entity& EntityManager::getEntity(int UID) {
    auto entity = entities.find(UID);
    return entity->second;
}

