cmake_minimum_required(VERSION 3.31)
project(digit-sim C)

set(CMAKE_C_COMPILER gcc)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -O3 -Wextra")

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set the CMake build type to Debug
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

include_directories(include)

# Find all source files in the src directory
# and add them to the SRC variable
file(GLOB SRC src/*.c)

add_executable(digit-sim ${SRC} main.c)

# Add test executable
add_executable(assign_test ${SRC} test/assign_test.c)

# Enable tests
enable_testing()
# Add a test for the digit-sim executable
add_test(NAME digit-sim-test
         COMMAND digit-sim
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
         )

# Add a test for the assign_test executable
add_test(NAME assign_test
         COMMAND assign_test
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
         )