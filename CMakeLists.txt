cmake_minimum_required(VERSION 3.20)
project(GameEngine VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Export compile commands for better IntelliSense
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Compiler-specific flags
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    # GCC specific flags
    add_compile_options(
        -Wall -Wextra -Wpedantic
        -Wcast-align -Wcast-qual -Wctor-dtor-privacy
        -Wdisabled-optimization -Wformat=2 -Winit-self
        -Wmissing-declarations -Wmissing-include-dirs
        -Wold-style-cast -Woverloaded-virtual -Wredundant-decls
        -Wshadow -Wsign-conversion -Wsign-promo
        -Wstrict-overflow=5 -Wswitch-default -Wundef
    )
    
    # Debug flags
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_compile_options(-g3 -O0 -DDEBUG)
        add_compile_definitions(_GLIBCXX_DEBUG)
    endif()
    
    # Release flags
    if(CMAKE_BUILD_TYPE STREQUAL "Release")
        add_compile_options(-O3 -DNDEBUG)
    endif()
endif()

# Enable testing
enable_testing()

# Include directories
include_directories(include)

# Find or fetch Google Test
find_package(GTest QUIET)
if(NOT GTest_FOUND)
    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
    )
    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
endif()

# Source files for the engine library
file(GLOB_RECURSE ENGINE_SOURCES "src/Core/*.cpp")
file(GLOB_RECURSE ENGINE_HEADERS "include/GameEngine/*.h")

# Create engine library (excluding main.cpp)
add_library(GameEngineLib ${ENGINE_SOURCES} ${ENGINE_HEADERS})
target_include_directories(GameEngineLib PUBLIC include)

# Set properties for the library
set_target_properties(GameEngineLib PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

# Main executable
add_executable(GameEngine src/main.cpp)
target_link_libraries(GameEngine GameEngineLib)

# Set properties for the executable
set_target_properties(GameEngine PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

# Test executable
file(GLOB_RECURSE TEST_SOURCES "tests/*.cpp")
add_executable(GameEngineTests ${TEST_SOURCES})
target_link_libraries(GameEngineTests 
    GameEngineLib 
    gtest 
    gtest_main
    pthread  # Required for GTest on Linux
)

# Set properties for tests
set_target_properties(GameEngineTests PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

# Register tests with CTest
include(GoogleTest)
gtest_discover_tests(GameEngineTests)

# Copy assets to build directory
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

# Print some useful information
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ Compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "C++ Compiler version: ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "System: ${CMAKE_SYSTEM_NAME}")