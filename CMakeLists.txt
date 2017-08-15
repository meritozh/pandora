cmake_minimum_required(VERSION 2.6)

project(pandora)

if(NOT DEFINED CMAKE_MACOSX_RPATH)
    set(CMAKE_MACOSX_RPATH 0)
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB SOURCE_SUPPORT "lib/Support/*.cpp" )

add_library(pandora SHARED ${SOURCE_SUPPORT})
