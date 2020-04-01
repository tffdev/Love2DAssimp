cmake_minimum_required(VERSION 3.15)
project(Love2DAssimp)

set(CMAKE_CXX_STANDARD 14)

#include_directories(/usr/include)
#link_directories(/usr/lib)
include_directories(C:/Users/Daniel/Desktop/assimp_dev C:/cygwin64/usr/include/lua-5.1)
link_directories(C:/Users/Daniel/Desktop/assimp_dev)
link_libraries(lua51 assimp)

add_library(Love2DAssimp SHARED src/library.cpp src/ModelBuilder.cpp src/ModelBuilder.h)