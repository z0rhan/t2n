cmake_minimum_required(VERSION 3.28)

# Project name
project(text2num)

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Source files
set(SOURCE_FILES
    src/main.cpp
    src/parser.cpp)

# Your executable
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
