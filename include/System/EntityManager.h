//
// Created by Jacob Ross on 3/24/24.
//

#ifndef BLOOM_ENGINE_ENTITYMANAGER_H
#define BLOOM_ENGINE_ENTITYMANAGER_H


#include <vector>
#include <unordered_map>
#include "../Entity/Entity.h"
#include "../Component/Texture.h"

class EntityManager {
public:
    int nextUID = 1;
    EntityManager();
    std::unordered_map<int, Entity> entities;

    int createEntity();

    Entity& getEntity(int UID);

    bool hasComponent(int entityUID, const std::string& componentType);


    template<typename T>
    std::vector<int> getEntitiesWithComponent(T& component) {
        std::vector<int> entitiesWithComponent;
        for (const auto& [entityUID, entity] : entities) {
            // Check if the entity has the specified component
            if (entity.components.find(component.type) != entity.components.end()) {
                entitiesWithComponent.push_back(entityUID);
            }
        }
        return entitiesWithComponent;
    }

    template<typename T>
    T& getEntityComponent(Entity& entity, const char *componentType) {
        auto component = entity.components.find(componentType);
        static_assert(std::is_base_of<Component, T>::value, "T must be a subclass of Component");
        return dynamic_cast<T&>(*component->second);
    }

    std::unordered_map<std::string, std::shared_ptr<Component>>& getEntityComponents(int UID);

    void attachComponent(int entityUID, Component* component);
};

#endif //BLOOM_ENGINE_ENTITYMANAGER_H
