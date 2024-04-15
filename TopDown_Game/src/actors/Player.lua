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
    setTexture(entityUID, "../TopDown_Game/assets/animation/hero_WalkCycleDown1.png")
    setRenderLayer(entityUID, RenderLayer.character)
    setTransform(entityUID, posX, posY)
    setPhysics(entityUID, 0, 0, 250, PhysicsMode.TopDown, 0, 0);
    setCamera(entityUID, posX, posY, 1280, 720);
    setBoundaryBox(entityUID, posX, posY, 32, 32)
    setBank(entityUID, "../TopDown_Game/assets/audio/Desktop/Player.bank");
    loadBank("../TopDown_Game/assets/audio/Desktop/Player.bank");


    -- Load WalkCycleDown
    addFrame(entityUID, AnimationType.WalkCycleDown, "../TopDown_Game/assets/animation/hero_WalkCycleDown1.png")
    addFrame(entityUID, AnimationType.WalkCycleDown, "../TopDown_Game/assets/animation/hero_WalkCycleDown2.png")
    addFrame(entityUID, AnimationType.WalkCycleDown, "../TopDown_Game/assets/animation/hero_WalkCycleDown3.png")
    addFrame(entityUID, AnimationType.WalkCycleDown, "../TopDown_Game/assets/animation/hero_WalkCycleDown4.png")
    addFrame(entityUID, AnimationType.WalkCycleDown, "../TopDown_Game/assets/animation/hero_WalkCycleDown5.png")

    --Load WalkCycleUp
    addFrame(entityUID, AnimationType.WalkCycleUp, "../TopDown_Game/assets/animation/hero_WalkCycleUp1.png")
    addFrame(entityUID, AnimationType.WalkCycleUp, "../TopDown_Game/assets/animation/hero_WalkCycleUp2.png")
    addFrame(entityUID, AnimationType.WalkCycleUp, "../TopDown_Game/assets/animation/hero_WalkCycleUp3.png")
    addFrame(entityUID, AnimationType.WalkCycleUp, "../TopDown_Game/assets/animation/hero_WalkCycleUp4.png")
    addFrame(entityUID, AnimationType.WalkCycleUp, "../TopDown_Game/assets/animation/hero_WalkCycleUp5.png")

    --Load WalkCycleLeft
    addFrame(entityUID, AnimationType.WalkCycleLeft, "../TopDown_Game/assets/animation/hero_WalkCycleLeft1.png")
    addFrame(entityUID, AnimationType.WalkCycleLeft, "../TopDown_Game/assets/animation/hero_WalkCycleLeft2.png")
    addFrame(entityUID, AnimationType.WalkCycleLeft, "../TopDown_Game/assets/animation/hero_WalkCycleLeft3.png")
    addFrame(entityUID, AnimationType.WalkCycleLeft, "../TopDown_Game/assets/animation/hero_WalkCycleLeft4.png")
    addFrame(entityUID, AnimationType.WalkCycleLeft, "../TopDown_Game/assets/animation/hero_WalkCycleLeft5.png")

    --Load WalkCycleRight
    addFrame(entityUID, AnimationType.WalkCycleRight, "../TopDown_Game/assets/animation/hero_WalkCycleRight1.png")
    addFrame(entityUID, AnimationType.WalkCycleRight, "../TopDown_Game/assets/animation/hero_WalkCycleRight2.png")
    addFrame(entityUID, AnimationType.WalkCycleRight, "../TopDown_Game/assets/animation/hero_WalkCycleRight3.png")
    addFrame(entityUID, AnimationType.WalkCycleRight, "../TopDown_Game/assets/animation/hero_WalkCycleRight4.png")
    addFrame(entityUID, AnimationType.WalkCycleRight, "../TopDown_Game/assets/animation/hero_WalkCycleRight5.png")

    return Player ;
end

-- General move function
state = "idle";
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
function Player.moveUp(KeyCode)
    logMessage("[INFO] Lua Player.moveUp() Called with KeyCode: " .. KeyCode);
    dispatchEvent(entityUID, EventType.InputKeyDown, KeyCode);
    isMovingUp = true;
    state = "movingUp";
    triggerAnimationChange(entityUID, "movingUp")
end

function Player.stopMoveUp(KeyCode)
    logMessage("[INFO] Lua Player.stopMoveUp() Called with KeyCode: " .. KeyCode);
    dispatchEvent(entityUID, EventType.InputKeyUp, KeyCode);
    isMovingUp = false;
    state = "idle";
    triggerAnimationChange(entityUID, "idle");
end

function Player.moveDown(KeyCode)
    logMessage("[INFO] Lua Player.moveDown() Called with KeyCode: " .. KeyCode);
    dispatchEvent(entityUID, EventType.InputKeyDown, KeyCode);
    isMovingDown = true;
    state = "movingDown";
    triggerAnimationChange(entityUID, "movingDown")
end

function Player.stopMoveDown(KeyCode)
    logMessage("[INFO] Lua Player.stopMoveDown() Called");
    dispatchEvent(entityUID, EventType.InputKeyUp, KeyCode);
    isMovingDown = false;
    state = "idle";
    triggerAnimationChange(entityUID, "idle");
end

function Player.moveLeft(KeyCode)
    logMessage("[INFO] Lua Player.moveLeft() Called");
    dispatchEvent(entityUID, EventType.InputKeyDown, KeyCode);
    isMovingLeft = true;
    state = "movingLeft";
    triggerAnimationChange(entityUID, "movingLeft");
end

function Player.stopMoveLeft(KeyCode)
    logMessage("[INFO] Lua Player.stopMoveLeft() Called");
    dispatchEvent(entityUID, EventType.InputKeyUp, KeyCode);
    isMovingLeft = false;
    state = "idle";
    triggerAnimationChange(entityUID, "idle");
end

function Player.moveRight(KeyCode)
    logMessage("[INFO] Lua Player.moveRight() Called");
    dispatchEvent(entityUID, EventType.InputKeyDown, KeyCode);
    isMovingRight = true;
    state = "movingRight";
    triggerAnimationChange(entityUID, "movingRight");
end

function Player.stopMoveRight(KeyCode)
    logMessage("[INFO] Lua Player.stopMoveRight() Called");
    dispatchEvent(entityUID, EventType.InputKeyUp, KeyCode);
    isMovingRight = false;
    state = "idle";
    triggerAnimationChange(entityUID, "idle");
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