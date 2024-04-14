//
// Created by Jacob Ross on 3/24/24.
//

/**
 * @file EntityManager.h
 * @brief Core system that orchestrates all entity management
 * The EntityManager system is responsible for entity creation, composition, and destruction. Each entity is stored in
 * a map by a unique identifier (entityUID). EntityManager can attach and remove specified ComponentType,
 * check is an entity has a specified ComponentType attached
 */

#ifndef BLOOM_ENGINE_ENTITYMANAGER_H
#define BLOOM_ENGINE_ENTITYMANAGER_H

#include <vector>
#include <unordered_map>

#include "Entity.h"
#include "Animation.h"
#include "Audio.h"
#include "Camera.h"
#include "Collider.h"
#include "Component.h"
#include "Event.h"
#include "Physics.h"
#include "Player.h"
#include "Renderable.h"
#include "Sprite.h"
#include "Texture.h"
#include "Transform.h"

/**
 * @class EntityManager
 * @brief System class that orchestrates all Entity handling.
 * The EntityManager system manages Entity creation, composition, and destruction. Each entity created by the
 * EntityManager is stored in an unordered map by it's assigned unique identifier (entityUID).
 */
class EntityManager {
public:

    /**
     * @brief EntityManager's constructor.
     */
    EntityManager();

    /**
     * @brief Stores all entity objects by their unique identifier (entityUID).
     * entities is an unordered_map that stores every Entity created by the EntityManager. Storing each Entity by it's
     * entityUID allows for fast Entity lookup by other Systems in the engine.
     */
    std::unordered_map<int, Entity> entities;

    /**
     * Creates a new Entity object and assigns it an entityUID, the Entity is then stored in the entities unordered
     * map. A Transform Component is attached to the Entity by default.
     * @return Returns the created Entity's (entityUID)
     */
    int createEntity();

    /**
     * Takes the provided entityUID and does a search on the entities container. If an Entity was found, the Entity
     * object is returned by reference.
     * @param entityUID
     * @return Entity object is returned by reference
     */
    Entity& getEntity(int entityUID);

    /**
     * @brief Destroys Entity object specified by an entityUID.
     * @param entityUID
     */
    void destroyEntity(int entityUID);

    /**
     * @brief Checks if an Entity has a specified ComponentType attached.
     * Accepts an entityUID and ComponentType, does a search on the entities container for the entityUID, then
     * checks if the Entity has the Component type attached. If the ComponentType is attached it returns True.
     * @param entityUID
     * @param componentType
     * @return Boolean value True if ComponentType was attached, False if not.
     */
    bool hasComponent(int entityUID, const ComponentType& componentType);

    // This function returns a vector full of all entityUIDs that possess the specified component
    /**
     * @brief Returns all entities that contain the specified ComponentType.
     * Iterates through the entities container, then for each Entity it iterates through the attached components and
     * checks if the Entity contains the specified Component. If it does, the entityUID is stored in a vector and the
     * vector is returned once all entities are checked.
     * @tparam T
     * @param componentType
     * @return Vector of entityUID's that contain specified component
     */
    template<typename T>
    std::vector<int> getEntitiesWithComponent(ComponentType componentType) {
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

    /**
     * @brief Returns Component object of specified ComponentType.
     * Takes an entityUID and ComponentType, gets the Entity object and searches for the ComponentType. If
     * ComponentType is found, the Component object is returned by reference
     * @tparam T
     * @param entityUID
     * @param componentType
     * @return
     */
     // TODO Update error handling if ComponentType is not attached to the Entity
    template<typename T>
    T& getEntityComponent(int entityUID, const ComponentType componentType) {
        auto& entity = getEntity(entityUID);
        auto component = entity.components.find(componentType);
        static_assert(std::is_base_of<Component, T>::value, "T must be a subclass of Component");
        return dynamic_cast<T&>(*component->second);
    }

    /**
     * @brief Creates Component object of specified ComponentType.
     * @param componentType
     * @return unique_ptr to created Component object
     */
    std::unique_ptr<Component> createComponent(ComponentType componentType);

    /**
     * @brief Calls createComponent() to create Component object and attach it to specified Entity.
     * @param entityUID
     * @param componentType
     */
    void attachComponent(int entityUID, ComponentType componentType);

    /**
     * @brief Destroys component object from Entity's attached components.
     * @param entityUID
     * @param componentType
     */
    void removeComponent(int entityUID, ComponentType componentType);

private:
    int nextUID = 1; ///< Stores the next Entity's entityUID

};

#endif //BLOOM_ENGINE_ENTITYMANAGER_H
