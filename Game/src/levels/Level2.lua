---
--- Generated by EmmyLua(https://github.com/EmmyLua)
--- Created by enki.
--- DateTime: 3/28/24 10:27 PM
---


MainMenuState = {}

function MainMenuState.enter()
    print("[INFO] Entering MainMenuState")
end

function MainMenuState.exit()
    print("Exiting MainMenuState")
end

function MainMenuState.update(deltaTime)
    -- Update logic here
end

function MainMenuState.render()
    -- Rendering logic here
end

GameplayState = {}

function GameplayState.enter()
    print("[INFO] Entering GameplayState 1")
end

function GameplayState.exit()
    print("Exiting GameplayStateState")
end

function GameplayState.update(deltaTime)
    -- Update logic here
end

function GameplayState.render()
    -- Rendering logic here
end

-- Register the state with a global or a specific Lua registry for states
-- This ensures GameStateRegistry is created if it doesn't exist
GameStateRegistry = GameStateRegistry or {}
GameStateRegistry["MainMenuState"] = MainMenuState

GameStateRegistry = GameStateRegistry or {}
GameStateRegistry["GameplayState"] = GameplayState


--Function to create backgroundPainting
function createBackgroundPainting()
    -- Create background painting entity
    backgroundPainting = createEntity()
    logMessage("[INFO] Lua created Entity: " .. backgroundPainting);

    -- Attach components to the entity
    attachComponent(backgroundPainting, ComponentTypes.Transform)
    attachComponent(backgroundPainting, ComponentTypes.Renderable)
    attachComponent(backgroundPainting, ComponentTypes.Sprite)
    attachComponent(backgroundPainting, ComponentTypes.Texture)
    attachComponent(backgroundPainting, ComponentTypes.Audio);
    setBank(backgroundPainting, "../Game/assets/audio/Desktop/World.bank")



    -- Set sprite, texture, render layer, and initial transform
    setSprite(backgroundPainting, 0, 0, 1280, 720)
    setTexture(backgroundPainting, "../Game/assets/background_Future_Magic_Forest_ISOGRAPHIC.png")
    setRenderLayer(backgroundPainting, RenderLayer.background)
    setTransform(backgroundPainting, 0, 0)
end



-- Function to create collision boxes
function createBoundaryBox(posX, posY, width, height)
    local boundaryBox = createEntity();
    attachComponent(boundaryBox, ComponentTypes.Transform);
    attachComponent(boundaryBox, ComponentTypes.Physics);
    attachComponent(boundaryBox, ComponentTypes.Collider);
    attachComponent(boundaryBox, ComponentTypes.Sprite);
    setTransform(boundaryBox, posX, posY);
    setBoundaryBox(boundaryBox, posX, -posY, width, height );
    setSprite(boundaryBox, posX, posY, 32, 32)

end



-- Function to create and setup a new entity
function createPlayerEntity(posX, posY, width, height)
    -- Create Player Object
    player = createEntity()
    logMessage("[INFO] Lua created Entity: " .. player);
    attachComponent(player, ComponentTypes.Player)
    attachComponent(player, ComponentTypes.Transform)
    attachComponent(player, ComponentTypes.Physics)
    attachComponent(player, ComponentTypes.Collider)
    attachComponent(player, ComponentTypes.Renderable)
    attachComponent(player, ComponentTypes.Sprite)
    attachComponent(player, ComponentTypes.Texture)
    attachComponent(player, ComponentTypes.Animation)
    attachComponent(player, ComponentTypes.Camera)
    attachComponent(player, ComponentTypes.Audio)
    setSprite(player, posX, posY, width, height)
    setTexture(player, "../Game/assets/hero_WalkCycleDown1.png")
    setRenderLayer(player, RenderLayer.character)
    setTransform(player, posX, posY)
    setCamera(player, posX, posY, 1280, 720);
    setBoundaryBox(player, posX, posY, 32, 32)
    setBank(player, "../Game/assets/audio/Desktop/Player.bank");

    -- Load WalkCycleDown
    addFrame(player, AnimationType.WalkCycleDown, "../Game/assets/hero_WalkCycleDown1.png")
    addFrame(player, AnimationType.WalkCycleDown, "../Game/assets/hero_WalkCycleDown2.png")
    addFrame(player, AnimationType.WalkCycleDown, "../Game/assets/hero_WalkCycleDown3.png")
    addFrame(player, AnimationType.WalkCycleDown, "../Game/assets/hero_WalkCycleDown4.png")
    addFrame(player, AnimationType.WalkCycleDown, "../Game/assets/hero_WalkCycleDown5.png")

    --Load WalkCycleUp
    addFrame(player, AnimationType.WalkCycleUp, "../Game/assets/hero_WalkCycleUp1.png")
    addFrame(player, AnimationType.WalkCycleUp, "../Game/assets/hero_WalkCycleUp2.png")
    addFrame(player, AnimationType.WalkCycleUp, "../Game/assets/hero_WalkCycleUp3.png")
    addFrame(player, AnimationType.WalkCycleUp, "../Game/assets/hero_WalkCycleUp4.png")
    addFrame(player, AnimationType.WalkCycleUp, "../Game/assets/hero_WalkCycleUp5.png")

    --Load WalkCycleLeft
    addFrame(player, AnimationType.WalkCycleLeft, "../Game/assets/hero_WalkCycleLeft1.png")
    addFrame(player, AnimationType.WalkCycleLeft, "../Game/assets/hero_WalkCycleLeft2.png")
    addFrame(player, AnimationType.WalkCycleLeft, "../Game/assets/hero_WalkCycleLeft3.png")
    addFrame(player, AnimationType.WalkCycleLeft, "../Game/assets/hero_WalkCycleLeft4.png")
    addFrame(player, AnimationType.WalkCycleLeft, "../Game/assets/hero_WalkCycleLeft5.png")

    --Load WalkCycleRight
    addFrame(player, AnimationType.WalkCycleRight, "../Game/assets/hero_WalkCycleRight1.png")
    addFrame(player, AnimationType.WalkCycleRight, "../Game/assets/hero_WalkCycleRight2.png")
    addFrame(player, AnimationType.WalkCycleRight, "../Game/assets/hero_WalkCycleRight3.png")
    addFrame(player, AnimationType.WalkCycleRight, "../Game/assets/hero_WalkCycleRight4.png")
    addFrame(player, AnimationType.WalkCycleRight, "../Game/assets/hero_WalkCycleRight5.png")

end





-- constructLevel is called from Core. All level design should go in constructLevel so hot reloading the Lua script
-- updates all entities
function constructLevel()
    logMessage("[INFO] Contructing level");


    --loadBank("../Game/assets/audio/Desktop/World.bank");

    logMessage("[INFO] World Constructed");


    createBackgroundPainting();
    loadEntityBank(backgroundPainting);
    playEvent("event:/world_music_background");
    createBoundaryBox(430, -30, 60, 40);
    createPlayerEntity(615, 600, 96, 128);
    loadEntityBank(player);
    logMessage("[INFO] Level Constructed");




end


