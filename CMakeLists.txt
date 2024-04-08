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

# ImGui

# Add the Sol2 include directory
include_directories(/usr/local/lib/sol2-develop/include)


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

target_link_libraries(Bloom_Engine ${SDL2_LIBRARIES} "/usr/local/Cellar/sdl2_image/2.8.2_1/lib/libSDL2_image.dylib"
                                    ${LUA_LIBRARIES})

# Include Lua headers
target_include_directories(Bloom_Engine PRIVATE ${LUA_INCLUDE_DIR})
