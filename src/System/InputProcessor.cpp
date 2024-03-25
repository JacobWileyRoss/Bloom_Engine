//
// Created by Jacob Ross on 3/24/24.
//

#include "../../include/System/InputProcessor.h"
#include "SDL.h"


void InputProcessor::ProcessInput() {
    const Uint8* state = SDL_GetKeyboardState(NULL);

    //Get all entityUID's with Player type
    Player playerType;
    std::vector<int> entities = entityManager.getEntitiesWithComponent(playerType);

    // For each Entity with Player type apply movement input
    for(auto entity : entities) {
        Entity currentEntity = entityManager.getEntity(entity);
        // This assumes the player entity always exists and has a Physics component.
        // You might want to add checks to ensure that's the case.
        Physics& physics = entityManager.getEntityComponent<Physics>(entityManager.getEntity(currentEntity.UID), "Physics");

        // Reset direction initially every frame
        physics.dirX = 0;
        physics.dirY = 0;

        // Then set based on current key state
        if (state[SDL_SCANCODE_W]) physics.dirY -= 1;
        if (state[SDL_SCANCODE_S]) physics.dirY += 1;
        if (state[SDL_SCANCODE_A]) physics.dirX -= 1;
        if (state[SDL_SCANCODE_D]) physics.dirX += 1;

        // Normalize direction to maintain consistent speed in all directions
        float magnitude = std::sqrt(physics.dirX * physics.dirX + physics.dirY * physics.dirY);
        if (magnitude > 0) {
            physics.dirX /= magnitude;
            physics.dirY /= magnitude;
        }

    }


}
