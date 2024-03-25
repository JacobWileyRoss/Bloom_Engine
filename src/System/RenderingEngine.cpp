//
// Created by Jacob Ross on 3/24/24.
//

#include "../../include/System/RenderingEngine.h"

SDL_Renderer* RenderingEngine::renderer = nullptr;

void RenderingEngine::Initialize(SDL_Window *window) {
    if (!window) {
        std::cerr << "[ERROR] Initialize called with null window." << std::endl;
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        std::cerr << "[ERROR] Create Renderer Error: " << SDL_GetError() << std::endl;
        return;
    }

    std::cout << "[INFO] RenderingEngine initialized successfully." << std::endl;
}

void RenderingEngine::setSprite(Entity& entity, float x, float y, float w, float h) {
    if (!renderer) {
        std::cerr << "[ERROR] Renderer not initialized, cannot set sprite." << std::endl;
        return;
    }

    std::cout << "[INFO] setSprite() called for entity ID: " << entity.UID << std::endl;
    auto spriteComponent = entityManager.getEntityComponent<Sprite>(entity, "Sprite");
    spriteComponent.rect.x = x;
    spriteComponent.rect.y = y;
    spriteComponent.rect.w = w;
    spriteComponent.rect.h = h;
    std::cout << "[INFO] Sprite set to x: " << x << ", y: " << y << ", w: " << w << ", h: " << h << std::endl;
}

void RenderingEngine::setTexture(Entity& entity, const char* filename) {
    if (!renderer) {
        std::cerr << "[ERROR] Renderer is not initialized, cannot set texture." << std::endl;
        return;
    }

    std::cout << "[INFO] setTexture() called for entity ID: " << entity.UID << " with filename: " << filename << std::endl;
    SDL_Surface* surface = IMG_Load(filename);
    if (!surface) {
        std::cerr << "[ERROR] Surface Error for " << filename << ": " << IMG_GetError() << std::endl;
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface); // Surface is no longer needed after texture creation

    if (!texture) {
        std::cerr << "[ERROR] Create Texture Error for " << filename << ": " << SDL_GetError() << std::endl;
        return;
    }

    auto& textureComponent = entityManager.getEntityComponent<Texture>(entity, "Texture");
    textureComponent.texture = texture;
    std::cout << "[INFO] Texture loaded and set successfully for entity ID: " << entity.UID << std::endl;
}

void RenderingEngine::update(std::unordered_map<int, Entity>& entities) {
    // Iterate through all entities to find those with both Transform and Sprite components
    for (auto& [entityUID, entity] : entities) {
        if (entityManager.hasComponent(entityUID, "Transform") && entityManager.hasComponent(entityUID, "Sprite")) {
            // Retrieve the Transform and Sprite components
            auto& transform = entityManager.getEntityComponent<Transform>(entity, "Transform");
            auto& sprite = entityManager.getEntityComponent<Sprite>(entity, "Sprite");

            // Update the sprite's rect to match the entity's transform
            sprite.rect.x = transform.posX;
            sprite.rect.y = transform.posY;
            // The width and height could be static or could also change dynamically based on the entity's state
            // If static, they are already set when the Sprite component is added to an entity
            // If dynamic, you should update them here based on the specific logic
        }
    }
}

void RenderingEngine::Render(std::unordered_map<int, Entity>& entities) {
    if (!renderer) {
        std::cerr << "[ERROR] Renderer not initialized, cannot render." << std::endl;
        return;
    }

    // Clear the screen and set it to black
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    Texture texture;
    for (auto entityUID : entityManager.getEntitiesWithComponent<Texture>(texture)) {
        auto entityIt = entities.find(entityUID);
        if (entityIt == entities.end()) {
            std::cerr << "[ERROR] Entity not found for UID: " << entityUID << std::endl;
            continue;
        }

        auto& transformComponent = entityManager.getEntityComponent<Transform>(entityIt->second, "Transform");
        auto& textureComponent = entityManager.getEntityComponent<Texture>(entityIt->second, "Texture");
        auto& spriteComponent = entityManager.getEntityComponent<Sprite>(entityIt->second, "Sprite");

        // Assuming spriteComponent.rect is already correctly set in the update phase
        // There's no need to call setSprite here as it should be done in the update phase

        if (textureComponent.texture) {
            std::cout << "Rendering texture at x: " << spriteComponent.rect.x << ", y: " << spriteComponent.rect.y
                      << ", w: " << spriteComponent.rect.w << ", h: " << spriteComponent.rect.h << std::endl;
            if (SDL_RenderCopyF(renderer, textureComponent.texture, NULL, &spriteComponent.rect) != 0) {
                std::cerr << "SDL_RenderCopy error: " << SDL_GetError() << std::endl;
            }
            std::cout << "[INFO] Rendered entity UID: " << entityUID << std::endl;
        } else {
            std::cerr << "[ERROR] Texture not loaded for entity UID: " << entityUID << std::endl;
        }
    }

    SDL_RenderPresent(renderer);
}

void RenderingEngine::Shutdown() {
    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
        std::cout << "[INFO] Renderer destroyed and RenderingEngine shutdown." << std::endl;
    }
}