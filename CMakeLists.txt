cmake_minimum_required(VERSION 3.26)
project(Until_Extraction LANGUAGES CXX)

# Specify the build output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# MinGW specific settings
if(MINGW)
    set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
endif()

# Build settings
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# Fetch SFML
include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

# Add executable
add_executable(main src/main.cpp
        src/Sprites/Sprite.cpp
        src/Sprites/Sprite.hpp
        src/Sprites/Player.cpp
        src/Sprites/Player.hpp
        src/Sprites/Enemy.cpp
        src/Sprites/Enemy.hpp
        src/GameEngine/State.hpp
        src/GameEngine/StateMachine.cpp
        src/GameEngine/StateMachine.hpp
        src/GameEngine/AssetManager.cpp
        src/GameEngine/AssetManager.hpp
        src/GameEngine/InputManager.cpp
        src/GameEngine/InputManager.hpp
        src/GameEngine/Game.cpp
        src/GameEngine/Game.hpp
        src/Screens/SplashScreenState.cpp
        src/Screens/SplashScreenState.hpp)

target_link_libraries(main PRIVATE sfml-graphics)
target_compile_features(main PRIVATE cxx_std_17)

add_custom_command(
        TARGET main POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        ${CMAKE_BINARY_DIR}/assets
        COMMENT "Copying assets directory to build output"
)

# Copy DLLs for Windows
if(WIN32)
    add_custom_command(
        TARGET main
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy 
        ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll 
        $<TARGET_FILE_DIR:main>
        VERBATIM)
endif()

# Add custom target for building and running
add_custom_target(run
    COMMAND ${CMAKE_COMMAND} -E env ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/main.exe
    DEPENDS main
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
    COMMENT "Running main executable with build"
    VERBATIM
)

# Add custom target for running only (without rebuild)
add_custom_target(run-only
    COMMAND ${CMAKE_COMMAND} -E env ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/main.exe
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
    COMMENT "Running main executable without rebuild"
    VERBATIM
)