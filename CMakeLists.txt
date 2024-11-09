# Date: 24/07/2024
#
# Description: This CMakeLists.txt file is used to build the project.
#
# To build the project, go into the project's directory and run:
# ./scripts/build.sh [dev] [test]

# Specify the minimum version for CMake and the project's name
cmake_minimum_required(VERSION 3.10)
project(Sudoku)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)

# Option to toggle development mode
option(DEVELOPMENT "Build the project in development mode" OFF)
message(STATUS "Development mode: ${DEVELOPMENT}")

# Option to build tests
option(TEST "Build tests" OFF)
message(STATUS "Build tests: ${TEST}")

# Add the main executable
add_executable(Sudoku src/sudoku.cpp)

# Include directories
target_include_directories(Sudoku PUBLIC "include/")

# External dependencies
# Include the findAndCheckDependency function
include(${CMAKE_SOURCE_DIR}/cmake/findAndCheckDependency.cmake)

# Add source files
file(GLOB_RECURSE PROJECT_SOURCES "src/*.cpp")
# Exclude main file to avoid duplication
list(REMOVE_ITEM PROJECT_SOURCES "${CMAKE_SOURCE_DIR}/src/sudoku.cpp")
target_sources(Sudoku PRIVATE ${PROJECT_SOURCES})

# Conditionally include spdlog in development mode
if(DEVELOPMENT)
        # Add spdlog
        find_and_check_dependency(PACKAGE spdlog)
        target_link_libraries(Sudoku PRIVATE spdlog::spdlog)
        # Define DEVELOPMENT preprocessor macro
        target_compile_definitions(Sudoku PRIVATE DEVELOPMENT=1)
endif()

# Conditionally build tests
if(TEST)
        enable_testing()
        add_subdirectory(test)
endif()