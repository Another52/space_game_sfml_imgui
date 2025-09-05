cmake_minimum_required(VERSION 3.28)
project(spacegame LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)
FetchContent_Declare(ImGui
    GIT_REPOSITORY https://github.com/ocornut/imgui
    GIT_TAG v1.91.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(ImGui)
FetchContent_GetProperties(ImGui SOURCE_DIR IMGUI_DIR)
set(IMGUI_SFML_FIND_SFML OFF)
FetchContent_Declare(ImGui-SFML
    GIT_REPOSITORY https://github.com/SFML/imgui-sfml
    GIT_TAG v3.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(ImGui-SFML)

add_executable("${CMAKE_PROJECT_NAME}" WIN32 src/main.cpp src/Player.cpp src/Enemy.cpp src/Bullet.cpp src/Background.cpp)

target_compile_features("${CMAKE_PROJECT_NAME}" PRIVATE cxx_std_17)
target_include_directories("${CMAKE_PROJECT_NAME}" PRIVATE headers/)
target_link_libraries("${CMAKE_PROJECT_NAME}" PRIVATE SFML::Graphics ImGui-SFML::ImGui-SFML)

if(TARGET SFML::Main)
    target_link_libraries("${CMAKE_PROJECT_NAME}" PRIVATE SFML::Main)
endif()

#code macros
target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/resources/")