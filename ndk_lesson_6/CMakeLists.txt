cmake_minimum_required(VERSION 3.10.2)

add_library(native_lib6
        SHARED
        src/main/cpp/native_lib.cpp
        src/main/cpp/util/GLUtils.cpp
        src/main/cpp/sample/TextureSample.cpp)

target_link_libraries(native_lib6
        log
        EGL
        GLESv3
        android)