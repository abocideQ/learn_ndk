cmake_minimum_required(VERSION 3.10.2)

include_directories(
        util
)

file(GLOB src-files
        ${CMAKE_SOURCE_DIR}*.cpp
        ${CMAKE_SOURCE_DIR}/*.cpp
        ${CMAKE_SOURCE_DIR}/util/*.cpp
        )

add_library(native_render SHARED ${src-files})

target_link_libraries(
        native_render

        GLESv3
        log)
#file GLOB:相对路径
#file(GLOB src-files
#        ${CMAKE_SOURCE_DIR}/*.cpp
#        ${CMAKE_SOURCE_DIR}/util/*.cpp)
#
#add_library(native_render SHARED ${src-files})


#add_library(
#        native_render
#
#        SHARED
#
#        ../jni/native_lib.cpp
#        util/GLProgram.cpp
#)