//
// Created by Jacob Ross on 3/24/24.
//

#ifndef BLOOM_ENGINE_ENTITYMANAGER_H
#define BLOOM_ENGINE_ENTITYMANAGER_H


#include <vector>
#include <unordered_map>
#include "../Entity/Entity.h"

#include "../Component/Animation.h"
#include "../Component/Collider.h"
#include "../Component/Component.h"
#include "../Component/ComponentTypes.h"
#include "../Component/Event.h"
#include "../Component/Physics.h"
#include "../Component/Player.h"
#include "../Component/Renderable.h"
#include "../Component/Sprite.h"
#include "../Component/Texture.h"
#include "../Component/Transform.h"


// A collection of all Component types stored as an enum for Component selection parameters in member functions


class EntityManager {
public:
    int nextUID = 1;
    EntityManager();

    // This stores all Entities in an unordered map using the entityUID as a key and the Entity object
    // itself as the value
    std::unordered_map<int, Entity> entities;

    // Creates a new Entity object and returns the entityUID of the new Entity
    int createEntity();

    Entity& getEntity(int UID);

    bool hasComponent(int entityUID, const ComponentTypes& componentType);


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
