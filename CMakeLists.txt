cmake_minimum_required(VERSION 3.28)

# Project name
project(text2num)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Source files
set(SOURCE_FILES
    src/error.cpp
    src/parser.cpp)

# Your executable
add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${CMAKE_SOURCE_DIR}/include/t2n
)

# test
add_executable(text2num_test test/main.cpp)

target_link_libraries(text2num_test PRIVATE ${PROJECT_NAME})

target_include_directories(text2num_test PRIVATE ${CMAKE_SOURCE_DIR}/include)

