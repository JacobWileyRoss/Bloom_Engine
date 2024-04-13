//
// Created by Jacob Ross on 3/24/24.
//

/**
 * @file InputProcessor.h
 * @brief Header file for the InputProcessor class in Bloom Engine.
 *
 * The InputProcessor class is responsible for handling user input and dispatching
 * appropriate events to the rest of the engine. It interprets SDL events and translates
 * them into engine-specific events that are then dispatched through the Dispatcher.
 */

#ifndef BLOOM_ENGINE_INPUTPROCESSOR_H
#define BLOOM_ENGINE_INPUTPROCESSOR_H

#include "Entity.h"
#include "EntityManager.h"
#include "Dispatcher.h"
#include "Event.h"
#include "Player.h"
#include "Transform.h"
#include "Physics.h"

/**
 * @class InputProcessor
 * @brief Processes user input and dispatches engine events.
 *
 * The InputProcessor is a key component of the Bloom Engine that listens for SDL input
 * events, interprets them, and then creates and dispatches corresponding engine events
 * to influence the game state or behavior of entities.
 */
class InputProcessor {
public:
    /**
    * Constructs an InputProcessor with references to the EntityManager and Dispatcher.
    * @param entityManager A reference to the engine's EntityManager to access and manipulate entities.
    * @param dispatcher A reference to the Dispatcher to dispatch interpreted input events.
    */
    explicit InputProcessor(EntityManager& entityManager, Dispatcher& dispatcher)
            : entityManager(entityManager), dispatcher(dispatcher) {};

    /**
     * Processes SDL input events and dispatches corresponding engine events.
     * This function is called within the engine's main loop to handle events such as
     * keyboard presses, mouse movements, etc., and translate them into actions within the game.
     * @param event A reference to the current SDL_Event to be processed.
     */
    void ProcessInput(SDL_Event& event);

private:
    EntityManager& entityManager; ///< Reference to the engine's entity manager.
    Dispatcher& dispatcher; ///< Reference to the engine's event dispatcher.
    EventData eventData; ///< Struct to hold processed event data before dispatching.

};


#endif //BLOOM_ENGINE_INPUTPROCESSOR_H
