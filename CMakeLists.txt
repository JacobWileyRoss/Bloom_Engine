cmake_minimum_required(VERSION 3.27)
project(Bloom_Engine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${BLOOM_ENGINE_SOURCE_DIR}/cmake/modules")

# Include Lua
find_package(Lua REQUIRED)

# Include SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Include SDL2_image
set(SDL2_IMAGE_INCLUDE_DIR "/usr/local/Cellar/sdl2_image/2.8.2_1/include/SDL2")
find_package(SDL2_image REQUIRED)
message("SDL2_image include dirs: ${SDL2_IMAGE_INCLUDE_DIRS}")
message("SDL2_image libraries: ${SDL2_IMAGE_LIBRARIES}")
include_directories(${SDL2_IMAGE_INCLUDE_DIR})

# Add the Sol2 include directory
include_directories(/usr/local/lib/sol2-develop/include)


add_executable(Bloom_Engine main.cpp
        src/System/RenderingEngine.cpp
        include/System/RenderingEngine.h
        src/System/PhysicsEngine.cpp
        include/System/PhysicsEngine.h
        src/System/InputProcessor.cpp
        include/System/InputProcessor.h
        src/System/EntityManager.cpp
        include/System/EntityManager.h
        src/System/Dispatcher.cpp
        include/System/Dispatcher.h
        src/System/Core.cpp
        include/System/Core.h
        include/Entity/Entity.h
        src/Component/Component.cpp
        include/Component/Component.h
        include/Component/Event.h
        include/Component/Physics.h
        include/Component/Player.h
        include/Component/Renderable.h
        include/Component/Sprite.h
        include/Component/Texture.h
        include/Component/Transform.h
        include/Component/Collider.h
        src/System/CollisionEngine.cpp
        include/System/CollisionEngine.h
        include/Component/ComponentTypes.h
        include/Component/Animation.h
        src/System/AnimationEngine.cpp
        include/System/AnimationEngine.h
        src/System/ScriptingEngine.cpp
        include/System/ScriptingEngine.h
        src/System/FileSystem.cpp
        include/System/FileSystem.h
        src/System/StateMachine.cpp
        include/System/StateMachine.h
        include/GameState/GameState.h
        Game/State/GameplayState.h
        include/GameState/LuaGameState.h
        include/Component/Camera.h)

target_link_libraries(Bloom_Engine ${SDL2_LIBRARIES} "/usr/local/Cellar/sdl2_image/2.8.2_1/lib/libSDL2_image.dylib"
                                    ${LUA_LIBRARIES})

# Include Lua headers
target_include_directories(Bloom_Engine PRIVATE ${LUA_INCLUDE_DIR})
