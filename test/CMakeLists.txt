# Date: 24/07/2024
#
# Description: This CMakeLists.txt file is used to build the test executable
# for the project.
#
# Note: This is not intended to be a standalone CMakeLists.txt file.
#
# To build the tests, go into the project's build directory and run:
# ./scripts/build.sh test

# Automatically include all test source files from the test/src directory
file(GLOB_RECURSE TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

# Automatically include all source files from the src directory
file(GLOB_RECURSE SRC_SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")

# Define the main library target
add_library(SudokuLib ${SRC_SOURCES})

# Include the header files from the main include directory
target_include_directories(SudokuLib PUBLIC "${CMAKE_SOURCE_DIR}/include")

# Define the test executable "Test" and specify the test source files
add_executable(Test ${TEST_SOURCES})

# Include the header files from the main include directory and test include directory
target_include_directories(Test PRIVATE "${CMAKE_SOURCE_DIR}/include")
target_include_directories(Test PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")

# External dependencies
# Include the findAndCheckDependency function
include("${CMAKE_SOURCE_DIR}/cmake/findAndCheckDependency.cmake")

# Find and include the Google Test package
find_and_check_dependency(PACKAGE GTest REQUIRED)

# Link the test executable with the main library and Google Test
target_link_libraries(Test PRIVATE SudokuLib GTest::GTest GTest::Main)

# Define TEST preprocessor macro
target_compile_definitions(Test PRIVATE TEST=1)

# Conditionally include spdlog in development mode
if(DEVELOPMENT)
        # Add spdlog
        find_and_check_dependency(PACKAGE spdlog REQUIRED)
        target_link_libraries(Test PRIVATE spdlog::spdlog)
        # Define DEVELOPMENT preprocessor macro
        target_compile_definitions(Test PRIVATE DEVELOPMENT=1)
endif()

# Add the test to CMake's testing framework
add_test(NAME Test COMMAND Test)