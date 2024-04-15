---
--- Generated by EmmyLua(https://github.com/EmmyLua)
--- Created by enki.
--- DateTime: 3/28/24 10:27 PM
---


-- Load GameStates
package.path = package.path .. ";../Game/src/core/?.lua"
local GameStateRegistry = require "GameStates" -- Adjust the path as necessary


-- Add the directory containing the Player.lua module to the Lua package path
-- Path should be relative to the runtime directory of the executable
package.path = package.path .. ";../Game/src/actors/?.lua"

-- Now require the Player module without specifying the '.lua' extension
local player = require("Player")


--Function to create backgroundPainting
function createBackgroundPainting()
    -- Create background painting entity
    local backgroundPainting = createEntity()
    logMessage("[INFO] Lua created Entity: " .. backgroundPainting);

    -- Attach components to the entity
    attachComponent(backgroundPainting, ComponentType.Transform)
    attachComponent(backgroundPainting, ComponentType.Renderable)
    attachComponent(backgroundPainting, ComponentType.Sprite)
    attachComponent(backgroundPainting, ComponentType.Texture)

    -- Set sprite, texture, render layer, and initial transform
    setSprite(backgroundPainting, 0, 0, 1280, 720)
    setTexture(backgroundPainting, "../Game/assets/background_DarkPath_Ritual_Scene.png")
    setRenderLayer(backgroundPainting, RenderLayer.background)
    setTransform(backgroundPainting, 0, 0)
end

function createBackgroundPainting2()
    -- Create background painting entity
    local backgroundPainting = createEntity()
    logMessage("[INFO] Lua created Entity: " .. backgroundPainting);

    -- Attach components to the entity
    attachComponent(backgroundPainting, ComponentType.Transform)
    attachComponent(backgroundPainting, ComponentType.Renderable)
    attachComponent(backgroundPainting, ComponentType.Sprite)
    attachComponent(backgroundPainting, ComponentType.Texture)

    -- Set sprite, texture, render layer, and initial transform
    setSprite(backgroundPainting, 0, 0, 1280, 720)
    setTexture(backgroundPainting, "../Game/assets/background_DarkPath_Castle_Scene.png")
    setRenderLayer(backgroundPainting, RenderLayer.background)
    setTransform(backgroundPainting, 0, -720)
end


-- Function to create collision boxes
function createBoundaryBox(posX, posY, width, height)
    local boundaryBox = createEntity();
    attachComponent(boundaryBox, ComponentType.Transform);
    attachComponent(boundaryBox, ComponentType.Physics);
    attachComponent(boundaryBox, ComponentType.Collider);
    attachComponent(boundaryBox, ComponentType.Sprite);
    setTransform(boundaryBox, posX, posY);
    setBoundaryBox(boundaryBox, posX, -posY, width, height );
    setSprite(boundaryBox, posX, posY, 32, 32)

end



-- constructLevel is called from Core. All level design should go in constructLevel so hot reloading the Lua script
-- updates all entities
function constructLevel()
    logMessage("[INFO] Contructing level");
    loadBank("../Game/assets/audio/Desktop/Master.bank");
    loadBank("../Game/assets/audio/Desktop/Master.strings.bank");
    createBackgroundPainting();
    createBackgroundPainting2();
    createBoundaryBox(430, -30, 60, 40);
    playerUID = player.createPlayerEntity(615, 600, 96, 128);
    loadEntityBank(playerUID);


end


