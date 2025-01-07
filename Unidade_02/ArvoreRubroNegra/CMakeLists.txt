cmake_minimum_required(VERSION 3.10)

project(Arvore_Rubro_Negra)

set(CMAKE_CXX_FLAGS "-W -Wfatal-errors -g -pedantic")

include_directories(include)
file(GLOB_RECURSE SOURCES "src/*.c")

add_executable(Arvore_Rubro_Negra ${SOURCES})
