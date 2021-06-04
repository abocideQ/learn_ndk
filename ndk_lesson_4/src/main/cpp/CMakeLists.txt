cmake_minimum_required(VERSION 3.10.2)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fno-rtti -fno-exceptions -Wall")
#file(GLOB src-files
#        ${CMAKE_SOURCE_DIR}*.cpp
#        ${CMAKE_SOURCE_DIR}/*.cpp
#        #        ${CMAKE_SOURCE_DIR}/util/*.cpp
#        )

add_library(
        native_lib
        SHARED
        ${CMAKE_CURRENT_SOURCE_DIR}/native_lib.cpp)
##ANDROID_PLATFORM_LEVEL=18
add_definitions("-DDYNAMIC_ES3")
set(OPENGL_LIB GLESv3)
find_library(LOG_LIB log)
set(ANDROID_LIB android)
target_link_libraries(native_lib
        ${OPENGL_LIB}
        EGL
        ${LOG_LIB}
        ${ANDROID_LIB})
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