cmake_minimum_required(VERSION 3.15)
project(Love2DAssimp)

set(CMAKE_CXX_STANDARD 14)

include_directories(/usr/include)
link_directories(/usr/lib)
link_libraries(lua51 assimp)

add_library(Love2DAssimp SHARED src/library.cpp src/ModelBuilder.cpp src/ModelBuilder.h)
