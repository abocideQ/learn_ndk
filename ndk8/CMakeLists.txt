cmake_minimum_required(VERSION 3.10.2)

include_directories(
        src/main/cpp/glm
        src/main/cpp/util
        src/main/cpp/sample
        src/main/cpp/egl
)

file(GLOB SOURCE
        src/main/cpp/*.cpp
        src/main/cpp/glm/*.cpp
        src/main/cpp/util/*.cpp
        src/main/cpp/egl/*.cpp
        src/main/cpp/sample/*.cpp)

add_library(native_lib8
        SHARED
        ${SOURCE}
        )

target_link_libraries(native_lib8
        log
        EGL
        GLESv3
        android)