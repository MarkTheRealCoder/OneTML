cmake_minimum_required(VERSION 3.29)
project(OneTML)

set(CMAKE_CXX_STANDARD 20)

add_executable(OneTML
        main.cpp
        components/Template.cpp
        components/RawMetaElement.cpp
        components/Schema.h)
