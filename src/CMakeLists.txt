cmake_minimum_required(VERSION 3.29)
project(OneTML)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable verbose linking and compilation to assist with debugging
set(CMAKE_VERBOSE_MAKEFILE ON)

# Find the nlohmann_json library
find_package(nlohmann_json 3.2.0 REQUIRED)

# Add the executable
add_executable(OneTML
        main.cpp
        system/ErrorGenerator.cpp
        configs/Configuration.cpp
        environment/ObjectTML.cpp
)

# Include directories for headers
target_include_directories(OneTML PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/configs
        ${CMAKE_CURRENT_SOURCE_DIR}/system
        ${CMAKE_CURRENT_SOURCE_DIR}/environment
)

# Link with external libraries
target_link_libraries(OneTML PRIVATE nlohmann_json::nlohmann_json)

# Ensure proper linking behavior for template instantiations
# This ensures all source files are compiled with the same visibility settings.
target_compile_options(OneTML PRIVATE
        -fvisibility=hidden
        -fvisibility-inlines-hidden
)
