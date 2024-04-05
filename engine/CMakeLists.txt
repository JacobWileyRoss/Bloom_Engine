cmake_minimum_required(VERSION 3.27)
project(BloomEngine)

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
include_directories(../vendor/sol2-develop/include)

# Specify where the public headers are
include_directories(include)

add_library(BloomEngine STATIC
        src/RenderingEngine.cpp
        include/BloomEngine/RenderingEngine.h
        src/PhysicsEngine.cpp
        include/BloomEngine/PhysicsEngine.h
        src/InputProcessor.cpp
        include/BloomEngine/InputProcessor.h
        src/EntityManager.cpp
        include/BloomEngine/EntityManager.h
        src/Dispatcher.cpp
        include/BloomEngine/Dispatcher.h
        src/Core.cpp
        include/BloomEngine/Core.h
        include/BloomEngine/Entity.h
        src/Component.cpp
        include/BloomEngine/Component.h
        include/BloomEngine/Event.h
        include/BloomEngine/Physics.h
        include/BloomEngine/Player.h
        include/BloomEngine/Renderable.h
        include/BloomEngine/Sprite.h
        include/BloomEngine/Texture.h
        include/BloomEngine/Transform.h
        include/BloomEngine/Collider.h
        src/CollisionEngine.cpp
        include/BloomEngine/CollisionEngine.h
        include/BloomEngine/ComponentTypes.h
        include/BloomEngine/Animation.h
        src/AnimationEngine.cpp
        include/BloomEngine/AnimationEngine.h
        src/ScriptingEngine.cpp
        include/BloomEngine/ScriptingEngine.h
        src/FileSystem.cpp
        include/BloomEngine/FileSystem.h
        src/StateMachine.cpp
        include/BloomEngine/StateMachine.h
        include/BloomEngine/GameState.h
        ../editor/Game/src/State/GameplayState.h
        include/BloomEngine/LuaGameState.h
        include/BloomEngine/Camera.h)

target_link_libraries(BloomEngine ${SDL2_LIBRARIES} "/usr/local/Cellar/sdl2_image/2.8.2_1/lib/libSDL2_image.dylib"
                                    ${LUA_LIBRARIES})

# Include Lua headers
target_include_directories(BloomEngine PRIVATE ${LUA_INCLUDE_DIR})

# Specify installation rules
install(TARGETS BloomEngine DESTINATION lib)
install(DIRECTORY include/BloomEngine DESTINATION include)
