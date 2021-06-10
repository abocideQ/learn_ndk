cmake_minimum_required(VERSION 3.10.2)

add_library(native_lib7
        SHARED
        src/main/cpp/native_lib.cpp
        src/main/cpp/util/GLUtils.cpp
        src/main/cpp/sample/MatrixSample.cpp
        )

target_link_libraries(native_lib7
        log
        EGL
        GLESv3
        android)