cmake_minimum_required(VERSION 3.10)

project(structFileIO)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

set(TEST_EXE_NAME tests)

add_subdirectory(src)
