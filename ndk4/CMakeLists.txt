cmake_minimum_required(VERSION 3.10.2)

add_library(native_lib4
        SHARED
        src/main/cpp/native_lib.cpp)

target_link_libraries(native_lib4
        log
        EGL
        GLESv3
        android)