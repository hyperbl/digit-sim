cmake_minimum_required(VERSION 3.31)
project(digit-sim)

set(CMAKE_C_COMPILER gcc)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -O3 -Wextra")

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set the CMake build type to Release
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

include_directories(include)

# Find all source files in the src directory
# and add them to the SRC variable
file(GLOB SRC src/*.c main.c)

add_executable(digit-sim ${SRC})

# Enable tests
enable_testing()
# Add a test for the digit-sim executable
add_test(NAME digit-sim-test
         COMMAND digit-sim
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
         )
