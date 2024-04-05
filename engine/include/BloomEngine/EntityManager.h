//
// Created by Jacob Ross on 3/24/24.
//

#ifndef BLOOM_ENGINE_ENTITYMANAGER_H
#define BLOOM_ENGINE_ENTITYMANAGER_H


#include <vector>
#include <unordered_map>
#include "Entity.h"

#include "Animation.h"
#include "Camera.h"
#include "Collider.h"
#include "Component.h"
#include "ComponentTypes.h"
#include "Event.h"
#include "Physics.h"
#include "Player.h"
#include "Renderable.h"
#include "Sprite.h"
#include "Texture.h"
#include "Transform.h"


// A collection of all Component types stored as an enum for Component selection parameters in member functions


class EntityManager {
public:
    int nextUID = 1;
    EntityManager();

    // This stores all Entities in an unordered map using the entityUID as a key and the Entity object
    // itself as the value
    std::unordered_map<int, Entity> entities;

    int createEntity();
    Entity& getEntity(int entityUID);
    void destroyEntity(int entityUID);
    bool hasComponent(int entityUID, const ComponentTypes& componentType);

    // This function returns a vector full of all entityUIDs that possess the specified component
    template<typename T>
    std::vector<int> getEntitiesWithComponent(ComponentTypes componentType) {
        std::vector<int> entitiesWithComponent;

        for (const auto& [entityUID, entity] : entities) {
            // Iterate over components of the entity
            for (const auto& component : entity.components) {
                if (component.first == componentType) {
                    entitiesWithComponent.push_back(entityUID);
                    break; // Found the component, no need to check further for this entity
                }
            }
        }
        return entitiesWithComponent;
    }

    // This function returns the actual component from the specified entityUID and component type
    template<typename T>
    T& getEntityComponent(int entityUID, const ComponentTypes componentType) {
        auto& entity = getEntity(entityUID);
        auto component = entity.components.find(componentType);
        static_assert(std::is_base_of<Component, T>::value, "T must be a subclass of Component");
        return dynamic_cast<T&>(*component->second);
    }

    std::unique_ptr<Component> createComponent(ComponentTypes componentType);
    void attachComponent(int entityUID, ComponentTypes);
};

#endif //BLOOM_ENGINE_ENTITYMANAGER_H
