cmake_minimum_required(VERSION 3.1)

project(pandora)

if(NOT DEFINED CMAKE_MACOSX_RPATH)
    set(CMAKE_MACOSX_RPATH 0)
endif()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDRAD_REQUIRED OFF)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB SOURCE_SUPPORT "lib/Support/*.cpp" )
file(GLOB SOURCE_ADT     "lib/ADT/*.cpp")

add_library(pandora SHARED ${SOURCE_SUPPORT}
                           ${SOURCE_ADT})
