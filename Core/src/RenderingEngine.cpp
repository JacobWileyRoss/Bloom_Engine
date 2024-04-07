//
// Created by Jacob Ross on 3/24/24.
//

#include "../include/RenderingEngine.h"

SDL_Renderer* RenderingEngine::renderer = nullptr;
SDL_Texture* RenderingEngine::renderTargetTexture = nullptr;


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

    // Initialize renderTargetTexture
    renderTargetTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 1280, 720);
    if (!renderTargetTexture) {
        std::cerr << "[ERROR] Failed to create render target texture: " << SDL_GetError() << std::endl;
    }

    std::cout << "[INFO] RenderingEngine initialized successfully." << std::endl;
}

// This function is used to define a Sprite Component's size and position. Used in entity composition
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

// This function accepts an image filepath and assigns it to a Texture Component's SDL_Texture*
void RenderingEngine::setTexture(int entityUID, std::string filename) {
    if (!renderer) {
        std::cerr << "[ERROR] Renderer is not initialized, cannot set texture." << std::endl;
        return;
    }

    Entity& entity = entityManager.getEntity(entityUID);
    std::cout << "[INFO] setTexture() called for entity ID: " << entity.UID << " with filename: "
              << filename << std::endl;

    SDL_Surface* surface = IMG_Load(filename.c_str());
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

// This function defines a Camera Component's position and viewport size
void RenderingEngine::setCamera(int entityUID, int posX, int posY, int width, int height) {
    auto& camera = entityManager.getEntityComponent<Camera>
            (entityUID, ComponentTypes::Camera);
    camera.viewPort.x = posX;
    camera.viewPort.y = posY;
    camera.viewPort.w = width;
    camera.viewPort.h = height;
}

void RenderingEngine::update(std::unordered_map<int, Entity>& entities) {

    // Find the camera entity
    auto cameraEntities = entityManager.getEntitiesWithComponent<Camera>
            (ComponentTypes::Camera);
    if (cameraEntities.empty()) {
        std::cerr << "No camera entity found." << std::endl;
        return;
    }

    int cameraEntityUID = cameraEntities[0]; // Assuming the first camera entity is the main camera
    auto& camera = entityManager.getEntityComponent<Camera>
            (cameraEntityUID, ComponentTypes::Camera);

    // Find the player entity
    auto playerEntities = entityManager.getEntitiesWithComponent<Player>
            (ComponentTypes::Player);
    if (playerEntities.empty()) {
        std::cerr << "No player entity found." << std::endl;
        return;
    }

    int playerEntityUID = playerEntities[0]; // Assuming the first player entity is the main player
    auto& playerTransform = entityManager.getEntityComponent<Transform>
            (playerEntityUID, ComponentTypes::Transform);

    // Center the camera on the player
    camera.viewPort.x = playerTransform.posX - (camera.viewPort.w / 2);
    camera.viewPort.y = playerTransform.posY - (camera.viewPort.h / 2);
    // TODO add constraints here to prevent the camera from showing areas outside of game world boundaries
}

// TODO I need to review the Render() function and make sure I completely understand it and determine if it's the best method
// This is the main function that handles all the actual rendering. Sorts renderable entities by their render layer
void RenderingEngine::Render(std::unordered_map<int, Entity>& entities) {
    if (!renderer) {
        std::cerr << "[ERROR] Renderer not initialized, cannot render." << std::endl;
        return;
    }

    SDL_SetRenderTarget(renderer, renderTargetTexture);

    // First, find the camera entity UID
    auto cameraEntityUIDs = entityManager.getEntitiesWithComponent<Camera>
            (ComponentTypes::Camera);

    if (cameraEntityUIDs.empty()) {
        std::cerr << "[ERROR] No camera entity found, cannot render." << std::endl;
        return;
    }

    // Assuming the first camera entity is the one to be used
    int cameraEntityUID = cameraEntityUIDs.front();
    auto& cameraComponent = entityManager.getEntityComponent<Camera>
            (cameraEntityUID, ComponentTypes::Camera);

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

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    // Render entities in sorted order according to the camera's viewport and zoom
    for (const auto& [entityUID, renderLayer] : renderableEntities) {
        if (entityManager.hasComponent(entityUID, ComponentTypes::Texture) &&
            entityManager.hasComponent(entityUID, ComponentTypes::Sprite)) {
            auto& textureComponent = entityManager.getEntityComponent<Texture>
                    (entityUID, ComponentTypes::Texture);
            auto& spriteComponent = entityManager.getEntityComponent<Sprite>
                    (entityUID, ComponentTypes::Sprite);
            auto& transformComponent = entityManager.getEntityComponent<Transform>
                    (entityUID, ComponentTypes::Transform);
            if (textureComponent.texture) {
                SDL_Rect renderQuad = {
                        static_cast<int>((transformComponent.posX - cameraComponent.viewPort.x) *
                                         cameraComponent.zoomLevel),
                        static_cast<int>((transformComponent.posY - cameraComponent.viewPort.y) *
                                         cameraComponent.zoomLevel),
                        static_cast<int>(spriteComponent.rect.w * cameraComponent.zoomLevel),
                        static_cast<int>(spriteComponent.rect.h * cameraComponent.zoomLevel),
                };
                if (SDL_RenderCopy(renderer, textureComponent.texture, NULL, &renderQuad) != 0) {
                    std::cerr << "[ERROR] SDL_RenderCopy error: " << SDL_GetError() << std::endl;
                }
            }
        }
    }
    //SDL_RenderPresent(renderer);
    SDL_SetRenderTarget(renderer, NULL); // Reset to default when done
}

// This function sets a Renderable Component's RenderLayer which is used for separating entities from background,
// character, foreground, etc
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
