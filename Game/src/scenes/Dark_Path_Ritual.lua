---
--- Dark_Path_Ritual.lua
--- Created by enki.
--- DateTime: 4/14/24 12:41 PM
---


-- Load GameStates
package.path = package.path .. ";../Game/src/core/?.lua"
local GameStateRegistry = require "GameStates" -- Adjust the path as necessary


-- Add the directory containing the Player.lua module to the Lua package path
-- Path should be relative to the runtime directory of the executable
package.path = package.path .. ";../Game/src/actors/?.lua"

-- Now require the Player module
local player = require("Player")


-- Binding movement functions to key events
registerKeyDownCallback(KeyCode.W, function() player.moveUp(KeyCode.W) end)
registerKeyUpCallback(KeyCode.W, function() player.stopMoveUp(KeyCode.W) end)

registerKeyDownCallback(KeyCode.S, function() player.moveDown(KeyCode.S) end)
registerKeyUpCallback(KeyCode.S, function() player.stopMoveDown(KeyCode.S) end)

registerKeyDownCallback(KeyCode.A, function() player.moveLeft(KeyCode.A) end)
registerKeyUpCallback(KeyCode.A, function() player.stopMoveLeft(KeyCode.A) end)

registerKeyDownCallback(KeyCode.D, function() player.moveRight(KeyCode.D) end)
registerKeyUpCallback(KeyCode.D, function() player.stopMoveRight(KeyCode.D) end)

function update(deltaTime)
    --logMessage("[INFO] Game script called update() with deltaTime: " .. deltaTime);
    player.update(deltaTime);
end

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



function handleInput()
    --logMessage("[INFO] LUA handleInput() called");
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
    setPhysics(playerUID, 0, 0, 10)
    loadEntityBank(playerUID);



end


