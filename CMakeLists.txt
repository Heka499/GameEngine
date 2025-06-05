cmake_minimum_required(VERSION 3.20)
project(GameEngine VERSION 1.0.0 LANGUAGES CXX)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Compiler flags
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Include directories
include_directories(include)

# Find or fetch Google Test
find_package(GTest QUIET)
if (NOT GTest_FOUND)
    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50f33f9142fd2d6828e70ecb14b7d7.zip
    )
    FetchContent_MakeAvailable(googletest)
endif()

# Source files for engine library
file(GLOB_RECURSE ENIGNE_SOURCES "src/Core/*.cpp")
file(GLOB_RECURSE ENGINE_HEADERS "include/GameEngine/*.h")

# Create the engine library
add_library(GameEngineLib ${ENGINE_SOURCES} ${ENGINE_HEADERS})
target_include_directories(GameEngineLib PUBLIC include)

# Main executable
add_executable(GameEngine src/main.cpp)
target_link_libraries(GameEngine GameEngineLib)

# Test executable
file(GLOB_RECURSE TEST_SOURCES "tests/*.cpp")
add_executable(GameEngineTests ${TEST_SOURCES})
target_link_libraries((GameEngineTests
    GameEngineLib
    gtest
    gtest_main
))

# Register tests with CTest
include(GoogleTest)
gtest_discover_tests(GameEngineTests)

# Copy assets to build directory
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})