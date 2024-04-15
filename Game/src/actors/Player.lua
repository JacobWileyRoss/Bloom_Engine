---
--- Player.lua
--- Created by enki.
--- DateTime: 4/14/24 1:51 PM
---



local Player = {}



-- Function to create and setup a new Player entity
function Player.createPlayerEntity(posX, posY, width, height)
    -- Create Player Object
    entityUID = createEntity();
    logMessage("[INFO] Lua Player.lua created Entity: " .. entityUID);
    attachComponent(entityUID, ComponentType.Player)
    attachComponent(entityUID, ComponentType.Transform)
    attachComponent(entityUID, ComponentType.Physics)
    attachComponent(entityUID, ComponentType.Collider)
    attachComponent(entityUID, ComponentType.Renderable)
    attachComponent(entityUID, ComponentType.Sprite)
    attachComponent(entityUID, ComponentType.Texture)
    attachComponent(entityUID, ComponentType.Animation)
    attachComponent(entityUID, ComponentType.Camera)
    attachComponent(entityUID, ComponentType.Audio)
    setSprite(entityUID, posX, posY, width, height)
    setTexture(entityUID, "../Game/assets/animation/hero_WalkCycleDown1.png")
    setRenderLayer(entityUID, RenderLayer.character)
    setTransform(entityUID, posX, posY)
    setPhysics(entityUID, 0, 0, 250);
    setCamera(entityUID, posX, posY, 1280, 720);
    setBoundaryBox(entityUID, posX, posY, 32, 32)
    setBank(entityUID, "../Game/assets/audio/Desktop/Player.bank");
    loadBank("../Game/assets/audio/Desktop/Player.bank");


    -- Load WalkCycleDown
    addFrame(entityUID, AnimationType.WalkCycleDown, "../Game/assets/animation/hero_WalkCycleDown1.png")
    addFrame(entityUID, AnimationType.WalkCycleDown, "../Game/assets/animation/hero_WalkCycleDown2.png")
    addFrame(entityUID, AnimationType.WalkCycleDown, "../Game/assets/animation/hero_WalkCycleDown3.png")
    addFrame(entityUID, AnimationType.WalkCycleDown, "../Game/assets/animation/hero_WalkCycleDown4.png")
    addFrame(entityUID, AnimationType.WalkCycleDown, "../Game/assets/animation/hero_WalkCycleDown5.png")

    --Load WalkCycleUp
    addFrame(entityUID, AnimationType.WalkCycleUp, "../Game/assets/animation/hero_WalkCycleUp1.png")
    addFrame(entityUID, AnimationType.WalkCycleUp, "../Game/assets/animation/hero_WalkCycleUp2.png")
    addFrame(entityUID, AnimationType.WalkCycleUp, "../Game/assets/animation/hero_WalkCycleUp3.png")
    addFrame(entityUID, AnimationType.WalkCycleUp, "../Game/assets/animation/hero_WalkCycleUp4.png")
    addFrame(entityUID, AnimationType.WalkCycleUp, "../Game/assets/animation/hero_WalkCycleUp5.png")

    --Load WalkCycleLeft
    addFrame(entityUID, AnimationType.WalkCycleLeft, "../Game/assets/animation/hero_WalkCycleLeft1.png")
    addFrame(entityUID, AnimationType.WalkCycleLeft, "../Game/assets/animation/hero_WalkCycleLeft2.png")
    addFrame(entityUID, AnimationType.WalkCycleLeft, "../Game/assets/animation/hero_WalkCycleLeft3.png")
    addFrame(entityUID, AnimationType.WalkCycleLeft, "../Game/assets/animation/hero_WalkCycleLeft4.png")
    addFrame(entityUID, AnimationType.WalkCycleLeft, "../Game/assets/animation/hero_WalkCycleLeft5.png")

    --Load WalkCycleRight
    addFrame(entityUID, AnimationType.WalkCycleRight, "../Game/assets/animation/hero_WalkCycleRight1.png")
    addFrame(entityUID, AnimationType.WalkCycleRight, "../Game/assets/animation/hero_WalkCycleRight2.png")
    addFrame(entityUID, AnimationType.WalkCycleRight, "../Game/assets/animation/hero_WalkCycleRight3.png")
    addFrame(entityUID, AnimationType.WalkCycleRight, "../Game/assets/animation/hero_WalkCycleRight4.png")
    addFrame(entityUID, AnimationType.WalkCycleRight, "../Game/assets/animation/hero_WalkCycleRight5.png")

    return Player ;
end

-- General move function
Player.isMovingUp = false
Player.isMovingDown = false
Player.isMovingLeft = false
Player.isMovingRight = false

function Player.move(dx, dy)
    local transform = getComponent(entityUID, "Transform")
    transform.posX = transform.posX + dx
    transform.posY = transform.posY + dy
end

-- Specific directional movements
function Player.moveUp(key)
    logMessage("[INFO] Lua Player.moveUp() Called");
    dispatchEvent(entityUID, EventType.InputKeyDown, key);
    isMovingUp = true;
end

function Player.stopMoveUp(key)
    logMessage("[INFO] Lua Player.stopMoveUp() Called");
    dispatchEvent(entityUID, EventType.InputKeyUp, key);
    isMovingUp = false;

end

function Player.moveDown(key)
    logMessage("[INFO] Lua Player.moveDown() Called");
    dispatchEvent(entityUID, EventType.InputKeyDown, key);
    isMovingDown = true;
end

function Player.stopMoveDown(key)
    logMessage("[INFO] Lua Player.stopMoveDown() Called");
    dispatchEvent(entityUID, EventType.InputKeyUp, key);
    isMovingDown = false;
end

function Player.moveLeft(key)
    logMessage("[INFO] Lua Player.moveLeft() Called");
    dispatchEvent(entityUID, EventType.InputKeyDown, key);
    isMovingLeft = true;
end

function Player.stopMoveLeft(key)
    logMessage("[INFO] Lua Player.stopMoveLeft() Called");
    dispatchEvent(entityUID, EventType.InputKeyUp, key);
    isMovingLeft = false;
end

function Player.moveRight(key)
    logMessage("[INFO] Lua Player.moveRight() Called");
    dispatchEvent(entityUID, EventType.InputKeyDown, key);
    isMovingRight = true;
end

function Player.stopMoveRight(key)
    logMessage("[INFO] Lua Player.stopMoveRight() Called");
    dispatchEvent(entityUID, EventType.InputKeyUp, key);
    isMovingRight = false;
end

-- Update function to apply continuous movement
function Player.update(deltaTime)
    if isMovingUp then
        -- Apply movement upward
        applyForce(entityUID, 0, -1)
    end
    if isMovingDown then
        -- Apply movement downward
        applyForce(entityUID, 0, 1)
    end
    if isMovingLeft then
        -- Apply movement to the left
        applyForce(entityUID, -1, 0)
    end
    if isMovingRight then
        -- Apply movement to the right
        applyForce(entityUID, 1, 0)
    end

end

return Player;