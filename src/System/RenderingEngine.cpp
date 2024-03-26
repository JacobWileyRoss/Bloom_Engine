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

void RenderingEngine::setSprite(int entityUID, float posX, float posY, float width, float height) {
    if (!renderer) {
        std::cerr << "[ERROR] Renderer not initialized, cannot set sprite." << std::endl;
        return;
    }

    std::cout << "[INFO] setSprite() called for entity ID: " << entityUID << std::endl;
    auto& spriteComponent = entityManager.getEntityComponent<Sprite>
            (entityUID, ComponentTypes::Sprite);
    spriteComponent.rect.x = posX;
    spriteComponent.rect.y = posY;
    spriteComponent.rect.w = width;
    spriteComponent.rect.h = height;
    std::cout << "[DEBUG] Sprite set to posX: " << posX << ", posY: " << posY << ", width: " << width << ", height: "
                << height << std::endl;
}

void RenderingEngine::setTexture(int entityUID, const char* filename) {
    if (!renderer) {
        std::cerr << "[ERROR] Renderer is not initialized, cannot set texture." << std::endl;
        return;
    }

    Entity& entity = entityManager.getEntity(entityUID);

    std::cout << "[INFO] setTexture() called for entity ID: " << entity.UID << " with filename: "
                << filename << std::endl;
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

    auto& textureComponent = entityManager.getEntityComponent<Texture>
            (entity.UID, ComponentTypes::Texture);
    textureComponent.texture = texture;
    std::cout << "[INFO] Texture loaded and set successfully for entity ID: " << entity.UID << std::endl;
}

void RenderingEngine::update(std::unordered_map<int, Entity>& entities) {
    // Iterate through all entities to find those with both Transform and Sprite components
    for (auto& [entityUID, entity] : entities) {
        if (entityManager.hasComponent(entityUID, ComponentTypes::Renderable)
        && entityManager.hasComponent(entityUID, ComponentTypes::Transform)
        && entityManager.hasComponent(entityUID, ComponentTypes::Sprite)) {
            // Retrieve the Transform and Sprite components
            auto& renderable = entityManager.getEntityComponent<Renderable>
                    (entityUID, ComponentTypes::Renderable);
            auto& transform = entityManager.getEntityComponent<Transform>
                    (entityUID, ComponentTypes::Transform);
            auto& sprite = entityManager.getEntityComponent<Sprite>
                    (entityUID, ComponentTypes::Sprite);

            // Update the sprite's rect to match the entity's transform
            sprite.rect.x = transform.posX;
            sprite.rect.y = transform.posY;
            std::cout << "[DEBUG] RenderingEngine::update() Sprite width: " << sprite.rect.w
                        << " Sprite height: " << sprite.rect.h << std::endl;
        }
    }
}

void RenderingEngine::Render(std::unordered_map<int, Entity>& entities) {
    if (!renderer) {
        std::cerr << "[ERROR] Renderer not initialized, cannot render." << std::endl;
        return;
    }

    // Gather all renderable entities
    std::vector<std::pair<int, RenderLayer>> renderableEntities;
    for (const auto& [entityUID, entity] : entities) {
        if (entityManager.hasComponent(entityUID, ComponentTypes::Renderable)) {
            auto& renderable = entityManager.getEntityComponent<Renderable>
                    (entityUID, ComponentTypes::Renderable);
            renderableEntities.push_back({entityUID, renderable.renderLayer});
        }
    }

    // Sort entities by their render layer
    std::sort(renderableEntities.begin(), renderableEntities.end(),
              [](const std::pair<int, RenderLayer>& a, const std::pair<int, RenderLayer>& b) {
                  return a.second < b.second;
              });

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    // Render entities in sorted order
    for (const auto& [entityUID, renderLayer] : renderableEntities) {
        // Check if entity has necessary components for rendering (e.g., Texture, Sprite)
        if (entityManager.hasComponent(entityUID, ComponentTypes::Texture) &&
            entityManager.hasComponent(entityUID, ComponentTypes::Sprite)) {
            auto& textureComponent = entityManager.getEntityComponent<Texture>
                    (entityUID, ComponentTypes::Texture);
            auto& spriteComponent = entityManager.getEntityComponent<Sprite>
                    (entityUID, ComponentTypes::Sprite);

            if (textureComponent.texture) {
                if (SDL_RenderCopyF(renderer, textureComponent.texture, NULL,
                                    &spriteComponent.rect) != 0) {
                    std::cerr << "[ERROR] SDL_RenderCopy error: " << SDL_GetError() << std::endl;
                }
            }
        }
    }

    SDL_RenderPresent(renderer);
}

void RenderingEngine::setRenderLayer(int entityUID, RenderLayer renderLayer) {
    auto& renderable = entityManager.getEntityComponent<Renderable>
            (entityUID, ComponentTypes::Renderable);
    renderable.renderLayer = renderLayer;
}

void RenderingEngine::Shutdown() {
    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
        std::cout << "[INFO] Renderer destroyed and RenderingEngine shutdown." << std::endl;
    }
}