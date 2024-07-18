cmake_minimum_required(VERSION 3.10)

project(structFileIO)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")
set(SRC_LIST main.cpp)

add_executable(structFileIO ${SRC_LIST})

