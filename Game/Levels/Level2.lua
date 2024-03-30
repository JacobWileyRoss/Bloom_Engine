---
--- Generated by EmmyLua(https://github.com/EmmyLua)
--- Created by enki.
--- DateTime: 3/28/24 11:16 PM
---



-- Table to define component types with their attachment functions for dynamic calls
local componentAttachmentFunctions = {
    Transform = function(entityID, config)
        attachComponent(entityID, ComponentTypes.Transform)
        -- Assume setTransform can accept a config table with x, y values
        setTransform(entityID, config.x, config.y)
    end,
    Renderable = function(entityID, config)
        attachComponent(entityID, ComponentTypes.Renderable)
    end,
    Sprite = function(entityID, config)
        -- Assume setSprite can accept a config table with x, y, width, height values
        setSprite(entityID, config.x, config.y, config.width, config.height)
    end,
    Texture = function(entityID, config)
        -- Assume setTexture can accept a config table with filename value
        setTexture(entityID, config.filename)
    end,
    -- Add other components as needed
}

-- Function to create a new entity and attach specified components with configurations
function createEntityWithComponents(componentsConfig)
    local newEntity = createEntity()

    for componentName, config in pairs(componentsConfig) do
        if componentAttachmentFunctions[componentName] then
            componentAttachmentFunctions[componentName](newEntity, config)
        else
            print("Warning: Component attachment function for '" .. componentName .. "' not found.")
        end
    end

    return newEntity
end

-- Create background painting
createEntityWithComponents({
    Transform = {x = 0, y = 0},
    Renderable = {},
    RenderLayer = {background},
    Sprite = {x = 0.0, y = 0.0, width = 1280, height = 720},
    Texture = {filename = "../Game/Assets/background_DarkPath_Castle_Scene.png"},
    -- Add other components as needed
})

-- Create Player entity
--createEntityWithComponents({
--    Player = {},
--    Transform = {x = 100, y = 100},
--    Renderable = {},
--    RenderLayer = {character},
--    Sprite = {x = 100, y = 100, width = 96, height = 128 },
--    Texture = {filename = '../Game/Assets/hero_WalkCycleDown1.png'}
--})