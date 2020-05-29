project(Freestyle)

cmake_minimum_required(VERSION 2.8.6)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

set(APPNAME Freestyle)
set(APPVERSION_MAJ 2)
set(APPVERSION_MID 2)
set(APPVERSION_MIN 0)
set(APPVERSION ${APPVERSION_MAJ}.${APPVERSION_MID}.${APPVERSION_MIN})

if(APPLE)
    add_definitions(-DGL_SILENCE_DEPRECATION)
endif()

find_package(Lib3ds)
include_directories(${Lib3ds_INCLUDE_DIRS})

set(EXECUTABLE_OUTPUT_PATH
    ${CMAKE_SOURCE_DIR}/../build/
)

set(LIBRARY_OUTPUT_PATH
    ${CMAKE_SOURCE_DIR}/../build/lib
)

add_subdirectory(geometry)

add_subdirectory(image)

add_subdirectory(scene_graph)

add_subdirectory(stroke)

add_subdirectory(system)

add_subdirectory(rendering)

add_subdirectory(view_map)

add_subdirectory(winged_edge)

add_subdirectory(swig)

add_subdirectory(app)

