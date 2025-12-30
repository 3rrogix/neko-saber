cmake_minimum_required(VERSION 3.21)
project(neko-saber)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/shared)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/extern)

# Source files
file(GLOB_RECURSE SOURCES src/*.cpp)

# Create the shared library
add_library(nekosaber SHARED ${SOURCES})

# Link libraries
target_link_libraries(nekosaber beatsaber-hook::beatsaber-hook paper::paper bsml::bsml custom-types::custom-types)

# Set properties
set_target_properties(nekosaber PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/../neko\ saber
    LIBRARY_OUTPUT_NAME libnekosaber
)