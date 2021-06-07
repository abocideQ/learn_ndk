cmake_minimum_required(VERSION 3.10.2)

add_library(native_lib5
        SHARED
        src/main/cpp/native_lib.cpp
        src/main/cpp/util/GLUtils.cpp
        src/main/cpp/sample/TriangleSample.cpp)

target_link_libraries(native_lib5
        log
        EGL
        GLESv3
        android)