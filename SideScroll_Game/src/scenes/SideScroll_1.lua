---
--- Generated by EmmyLua(https://github.com/EmmyLua)
--- Created by enki.
--- DateTime: 4/15/24 1:36 AM
---

-- Load GameStates
package.path = package.path .. ";../SideScroll_Game/src/core/?.lua"
local GameStateRegistry = require "GameStates" -- Adjust the path as necessary


-- Add the directory containing the Player.lua module to the Lua package path
-- Path should be relative to the runtime directory of the executable
package.path = package.path .. ";../SideScroll_Game/src/actors/?.lua"

-- Now require the Player module
local player = require("Player")

-- Binding movement functions to key events
registerKeyDownCallback(KeyCode.A, function() player.moveLeft(KeyCode.A) end)
registerKeyUpCallback(KeyCode.A, function() player.stopMoveLeft(KeyCode.A) end)

registerKeyDownCallback(KeyCode.D, function() player.moveRight(KeyCode.D) end)
registerKeyUpCallback(KeyCode.D, function() player.stopMoveRight(KeyCode.D) end)

registerKeyDownCallback(KeyCode.SPACE, function() player.jump(KeyCode.SPACE) end)
registerKeyUpCallback(KeyCode.SPACE, function() player.stopJump(KeyCode.SPACE) end)

function update(deltaTime)
    --logMessage("[INFO] TopDown_Game script called update() with deltaTime: " .. deltaTime);
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
    setSprite(backgroundPainting, 0, 0, 5120, 720)
    setTexture(backgroundPainting, "../SideScroll_Game/assets/background_Enchanted_Course_001.png")
    setRenderLayer(backgroundPainting, RenderLayer.background)
    setTransform(backgroundPainting, 0, 0)
end

function createBoundaryBox(posX, posY, width, height)
    local boundaryBox = createEntity();
    attachComponent(boundaryBox, ComponentType.Transform);
    attachComponent(boundaryBox, ComponentType.Physics);
    attachComponent(boundaryBox, ComponentType.Collider);
    attachComponent(boundaryBox, ComponentType.Sprite);
    setTransform(boundaryBox, posX, posY);
    setBoundaryBox(boundaryBox, posX, -posY, width, height );
    setSprite(boundaryBox, posX, posY, width, height);
    setPhysics(boundaryBox, 0, 0, 0, PhysicsMode.SideScroll, 0, 0);
end

function createPlatform(posX, posY, width, height)
    -- Create background painting entity
    local platform = createEntity()
    logMessage("[INFO] Lua created Entity: " .. platform);

    -- Attach components to the entity
    attachComponent(platform, ComponentType.Transform)
    attachComponent(platform, ComponentType.Renderable)
    attachComponent(platform, ComponentType.Sprite)
    attachComponent(platform, ComponentType.Texture)

    -- Set sprite, texture, render layer, and initial transform
    setSprite(platform, posX, posY, width, height)
    setTexture(platform, "../SideScroll_Game/assets/platform_Basic_001.png")
    setRenderLayer(platform, RenderLayer.foreground)
    setTransform(platform, posX, posY)
end


function constructLevel()
    logMessage("[INFO] Contructing level");
    loadBank("../SideScroll_Game/assets/audio/SideScroll_Game/Build/Desktop/Master.bank");
    loadBank("../SideScroll_Game/assets/audio/SideScroll_Game/Build/Desktop/Master.strings.bank");
    loadBank("../SideScroll_Game/assets/audio/SideScroll_Game/Build/Desktop/World.bank");
    playEvent("event:/Theme");
    createBackgroundPainting();

    createBoundaryBox(0, 610, 5120, 5);

    createBoundaryBox(800, 470, 200, 300);
    createBoundaryBox(1113, 335, 334, 29);
    createBoundaryBox(1710, 350, 200, 82);
    createBoundaryBox(2020, 200, 752, 33);
    createBoundaryBox(2040, 530, 200, 82);
    createBoundaryBox(2325, 410, 200, 82);
    createBoundaryBox(3300, 530, 200, 82);
    createBoundaryBox(3600, 350, 200, 82);
    createBoundaryBox(3845, 470, 240, 300);
    createBoundaryBox(4150, 370, 200, 82);
    createBoundaryBox(3840, 175, 752, 33);





    playerUID = player.createPlayerEntity(615, -200, 96, 128);
end

