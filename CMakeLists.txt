cmake_minimum_required(VERSION 2.8)

project(benchmark)

if (UNIX)
    add_definitions(-std=c++11)
endif()

include_directories(
    include
)

file(GLOB SRC 
    include/*.h # actually no need to add these in project
    benchmark.cpp
)
add_executable(benchmark ${SRC})
