//
// Created by Jacob Ross on 3/24/24.
//

#include "../include/InputProcessor.h"
#include "SDL.h"

// ProcessInput is called in the Core MainLoop() function if the SDL Event is detected as a SDL_Key event
void InputProcessor::ProcessInput(SDL_Event& event) { // Accept SDL_Event as parameter

        // Gets the entity with a Player component as that should be the only entity that processes user input
        // from the keyboard or mouse
        // TODO update ProcessInput so that it detects and supports mouse events
        std::vector<int> playerEntities = entityManager.getEntitiesWithComponent<Player>(ComponentTypes::Player);
        for (auto entityUID : playerEntities) {
            switch (event.type) {
                case SDL_KEYDOWN:
                    if (!event.key.repeat) { // Process keydown event
                        std::cout << "[INFO] Dispatching InputKeyDown event for Entity: " << entityUID << std::endl;
                        dispatcher.dispatchEvent(Event(entityUID, EventType::InputKeyDown, event.key.keysym.scancode));
                    }
                    break;
                case SDL_KEYUP: // Process keyup event
                    std::cout << "[INFO] Dispatching InputKeyUp event for Entity: " << entityUID << std::endl;
                    dispatcher.dispatchEvent(Event(entityUID, EventType::InputKeyUp, event.key.keysym.scancode));
                    break;
                //default:
                    //std::cout << "[WARNING] SDL_PollEvent unknown" << std::endl;
            }
        }

    // TODO ProcessInput() should process the actions defined by the ScriptingEngine and not be hard coded here
    // It's important to note that continuous key states are processed outside of specific key up/down events.
    // This section is for actions like continuous movement where the key's current state (pressed or not) matters.
    const Uint8* state = SDL_GetKeyboardState(NULL);
    for (auto entityUID : playerEntities) {
        Entity& currentEntity = entityManager.getEntity(entityUID);
        Physics& physics = entityManager.getEntityComponent<Physics>(entityUID, ComponentTypes::Physics);

        // Reset direction at the start of every frame to handle the current key state.
        physics.dirX = 0;
        physics.dirY = 0;

        // Then, set the direction based on the current state of WASD keys.
        if (state[SDL_SCANCODE_W]) physics.dirY -= 1;
        if (state[SDL_SCANCODE_S]) physics.dirY += 1;
        if (state[SDL_SCANCODE_A]) physics.dirX -= 1;
        if (state[SDL_SCANCODE_D]) physics.dirX += 1;

        // Normalize the direction vector to ensure consistent movement speed in all directions.
        float magnitude = std::hypot(physics.dirX, physics.dirY);
        if (magnitude > 0) {
            physics.dirX /= magnitude;
            physics.dirY /= magnitude;
        }
    }
}
