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
    return entityUID;
}

bool EntityManager::hasComponent(int entityUID, const std::string& componentType) {
    auto entityIt = entities.find(entityUID);
    if (entityIt != entities.end()) {
        // Check if the entity has the specified component type
        const auto& components = entityIt->second.components;
        return components.find(componentType) != components.end();
    }
    return false; // Entity not found or does not have the component
}

void EntityManager::attachComponent(int entityUID, Component *component) {
    auto entity = entities.find(entityUID);
    if (entity != entities.end()) {
        entity->second.components.emplace(component->type, component);
    } else {
        std::cerr << "Entity with UID " << entityUID << " not found!" << std::endl;
    }
}

Entity& EntityManager::getEntity(int UID) {
    auto entity = entities.find(UID);
    return entity->second;
}

std::unordered_map<std::string, std::shared_ptr<Component>>& EntityManager::getEntityComponents(int UID) {
    auto entity = entities.find(UID);
    if (entity != entities.end()) {
        return entity->second.components;
    }
}