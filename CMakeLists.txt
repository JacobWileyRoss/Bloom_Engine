cmake_minimum_required(VERSION 3.27)
project(Bloom_Engine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${BLOOM_ENGINE_SOURCE_DIR}/cmake/modules")

# Include Lua
set(LUA_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/vendor/lua/5.4.6/include/lua5.4")
set(LUA_LIBRARY "${CMAKE_CURRENT_SOURCE_DIR}/vendor/lua/5.4.6/lib/liblua5.4.dylib")
include_directories(${LUA_INCLUDE_DIR})
link_libraries(${LUA_LIBRARY})

# Add the Sol2 include directory
set(SOL2_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/vendor/sol2/include/")
include_directories(${SOL2_INCLUDE_DIR})

# Include SDL2
set(SDL2_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/vendor/sdl2")
set(SDL2_LIBRARY "${CMAKE_CURRENT_SOURCE_DIR}/vendor/sdl2/2.30.1/lib/") # Adjust extension as necessary
include_directories(${SDL2_IMAGE_INCLUDE_DIR})
link_directories(${SDL2_LIBRARY})

# Include SDL2_image
set(SDL2_IMAGE_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/vendor/sdl2_image")
set(SDL2_IMAGE_LIBRARY "${CMAKE_CURRENT_SOURCE_DIR}/vendor/sdl2_image/2.8.2_1/lib/") # Adjust extension as necessary
include_directories(${SDL2_IMAGE_INCLUDE_DIR})
link_directories(${SDL2_IMAGE_LIBRARY})

# ImGui source files
file(GLOB IMGUI_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui-docking/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui-docking/backends/imgui_impl_sdl2.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui-docking/backends/imgui_impl_sdlrenderer2.cpp" # Adjust this line as needed for your graphics API
)

# Include directories for ImGui and the backends
include_directories(
        "${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui-dockingr"
        "${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui-docking/backends"
)

add_executable(Bloom_Engine main.cpp
        ${IMGUI_SOURCES}
        vendor/ImGuiFileDialog-master/ImGuiFileDialog.cpp
        Core/src/RenderingEngine.cpp
        Core/include/RenderingEngine.h
        Core/src/PhysicsEngine.cpp
        Core/include/PhysicsEngine.h
        Core/src/InputProcessor.cpp
        Core/include/InputProcessor.h
        Core/src/EntityManager.cpp
        Core/include/EntityManager.h
        Core/src/Dispatcher.cpp
        Core/include/Dispatcher.h
        Core/src/Core.cpp
        Core/include/Core.h
        Core/include/Entity.h
        Core/src/Component.cpp
        Core/include/Component.h
        Core/include/Event.h
        Core/include/Physics.h
        Core/include/Player.h
        Core/include/Renderable.h
        Core/include/Sprite.h
        Core/include/Texture.h
        Core/include/Transform.h
        Core/include/Collider.h
        Core/src/CollisionEngine.cpp
        Core/include/CollisionEngine.h
        Core/include/ComponentTypes.h
        Core/include/Animation.h
        Core/src/AnimationEngine.cpp
        Core/include/AnimationEngine.h
        Core/src/ScriptingEngine.cpp
        Core/include/ScriptingEngine.h
        Core/src/FileSystem.cpp
        Core/include/FileSystem.h
        Core/src/StateMachine.cpp
        Core/include/StateMachine.h
        Core/include/GameState.h
        Game/src/GameplayState.h
        Core/include/LuaGameState.h
        Core/include/Camera.h
        Editor/include/Editor.cpp
        Editor/include/Editor.h
        Editor/include/OperationsLog.cpp
        Editor/include/OperationsLog.h
)

target_link_libraries(Bloom_Engine SDL2 SDL2_image ${LUA_LIBRARY})
target_include_directories(Bloom_Engine PRIVATE LUA)
