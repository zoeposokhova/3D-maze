cmake_minimum_required(VERSION 4.2)
project(3D_maze)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)
include_directories(src)

add_executable(3D_maze
        include/maze.h
        src/main.cpp
        src/maze.cpp
)
