cmake_minimum_required(VERSION 3.29)
project(OneTML)

set(CMAKE_CXX_STANDARD 20)

find_package(nlohmann_json 3.2.0 REQUIRED)

add_executable(OneTML
        main.cpp
        config/Resolver.cpp
        config/Path.h
        config/Path.cpp
)
target_link_libraries(OneTML PRIVATE nlohmann_json::nlohmann_json)
