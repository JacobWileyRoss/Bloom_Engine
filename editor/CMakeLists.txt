cmake_minimum_required(VERSION 3.27)
project(BloomEngineEditor)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)



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

include_directories(../vendor/sol2-develop/include)

# ImGui source files
file(GLOB IMGUI_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/../vendor/imgui-master/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/../vendor/imgui-master/backends/imgui_impl_sdl2.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/../vendor/imgui-master/backends/imgui_impl_sdlrenderer2.cpp" # Adjust this line as needed for your graphics API
)

# Include directories for ImGui and the backends
include_directories(
        "${CMAKE_CURRENT_SOURCE_DIR}/../vendor/imgui-master"
        "${CMAKE_CURRENT_SOURCE_DIR}/../vendor/imgui-master/backends"
)


# Assuming editor source files are in the editor/src directory
file(GLOB EDITOR_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

# Ensure the source files are being found
message("Editor sources: ${EDITOR_SOURCES}")

add_executable(BloomEngineEditor main.cpp
        ${IMGUI_SOURCES}
        ${EDITOR_SOURCES})


target_include_directories(BloomEngineEditor PRIVATE ${LUA_INCLUDE_DIR} PRIVATE ../engine/include )

# Link against the BloomEngine library
target_link_libraries(BloomEngineEditor PRIVATE BloomEngine )
