-- Define a global 'update' function that C++ will call each frame
function update(deltaTime)
   --logMessage("Lua: Updating game state with delta time: " .. deltaTime)
    -- Implement game logic here, potentially modifying game entities/components
end

function initialize()
   logMessage("[INFO] Lua initialized successfully")
end

