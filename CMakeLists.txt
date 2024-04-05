cmake_minimum_required(VERSION 3.27)
project(Bloom_EngineProject)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)

# Add the engine and editor directories
add_subdirectory(engine)
add_subdirectory(editor)
