---
--- Generated by EmmyLua(https://github.com/EmmyLua)
--- Created by enki.
--- DateTime: 4/7/24 12:42 PM
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
    print("[INFO] Entering GameplayState")
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


function createDefaultEntity(posX, posY, width, height)
    --local entity = createEntity();
    --attachComponent(entity, ComponentTypes.Camera);

end





-- constructLevel is called from Core. All level design should go in constructLevel so hot reloading the Lua script
-- updates all entities
function constructLevel()
    createDefaultEntity(0, 0, 32, 32);
    play("../Editor/assets/startup.mp3");
end


