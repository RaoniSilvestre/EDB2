cmake_minimum_required(VERSION 3.10)

project(Heap)

set(CMAKE_CXX_FLAGS "-W -Wfatal-errors -g -pedantic")

include_directories(include)
file(GLOB_RECURSE SOURCES "src/*.c")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_executable(Heap ${SOURCES})
