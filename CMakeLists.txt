cmake_minimum_required(VERSION 3.20)

project(wassio)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(${PROJECT_NAME}_interface INTERFACE)
target_include_directories(${PROJECT_NAME}_interface 
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)