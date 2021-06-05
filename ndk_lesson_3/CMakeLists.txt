#cmake_minimum_required(VERSION 3.4.1)
#指定 Cmake 需要的最低版本
##=========================================
## 设置项目名称 这个命令不是强制性的，但最好都加上。
## 它会引入两个变量 demo_BINARY_DIR 和 demo_SOURCE_DIR，同时，cmake 自动定义了两个等价的变量 PROJECT_BINARY_DIR 和 PROJECT_SOURCE_DIR。
#project(demo)
##=========================================
## 使用多个 add_library() 命令，您可以为 CMake 定义要从其他源文件构建的更多库。
##在 Linux 下是：
## xxx
## xxx.a
## xxx.so
##在 Windows 下是：
## xxx.exe
## xxx.lib
## xxx.dll
#add_executable(native_lib src/main/jni/native_lib.cpp) # 1.生成可执行文件
#add_library(native_lib STATIC src/main/jni/native_lib.cpp) # 2.生成静态库
#add_library(native_lib SHARED src/main/jni/native_lib.cpp) # 3.生成动态库或共享库
#add_library(native_lib src/main/jni/native_lib1.cpp src/main/jni/native_lib2.cpp) # 4.多个CPP生成一个
#aux_source_directory(. SRC_LIST) # 5.搜索当前目录下的所有.cpp文件
#add_library(demo ${SRC_LIST})   # 5.搜索当前目录下的所有.cpp文件
##=========================================
## 找到一个 NDK 的库，并且将这个库的路径存储在一个变量中。
## 例如上例中是找到 NDK 中的 log 库（Android 特定的日志支持库），
## 并将其路径存储在 “log-lib” 变量中，在后面你就可以通过 “${log-lib}” 命令取出变量中的值了。
#find_library(log_lib log)
##=========================================
##设置包含的目录,添加目录：头文件目录等
#为了让 CMake 能够在编译时找到头文件
#include_directories(
#        ${CMAKE_CURRENT_SOURCE_DIR}
#        ${CMAKE_CURRENT_BINARY_DIR}
#        ${CMAKE_CURRENT_SOURCE_DIR}/include
#)
##设置链接库搜索目录
#link_directories(
#        ${CMAKE_CURRENT_SOURCE_DIR}/libs
#)
##=========================================
## 关联库。将指定的库关联起来 。
#target_link_libraries(
#        # 目标库 add_library 所生成
#        native_lib
#        # 目标库需要链接的库 find_library 指定的变量名
#        ${log_lib})
#target_link_libraries(native_lib libface.a) # 链接libface.a
#target_link_libraries(native_lib libface.so) # 链接libface.so
#target_link_libraries(native_lib ${CMAKE_CURRENT_SOURCE_DIR}/libs/libface.so) # 链接libface.so
#target_link_libraries(native_lib            #指定链接多个库
#        ${CMAKE_CURRENT_SOURCE_DIR}/libs/libface.a
#        boost_system.a
#        boost_thread
#        pthread)
##=========================================
##设置变量
#set(SRC_LIST main.cpp test.cpp)
#add_library(demo ${SRC_LIST})
##=========================================
## gradle 中使用 cmake 的变量
##android {
##  defaultConfig {
##    externalNativeBuild {
##      cmake {
##        // 指定编译选项
##        cppFlags "-std=c++11 -frtti -fexceptions"
##        // 也向变量传递参数：
##        // arguments "-D变量名=参数".
##        arguments "-DANDROID_ARM_NEON=TRUE",
##        // 使用下面这种语法向变量传递多个参数（参数之间使用空格隔开）：
##        // arguments "-D变量名=参数1 参数2"
##        arguments "-DANDROID_CPP_FEATURES=rtti exceptions"
##        // 指定ABI
##        abiFilters "armeabi-v7a" , "arm64-v8a"
##      }
##    }
##  }
##  externalNativeBuild {
##    cmake {
##        path "CMakeLists.txt"
##    }
##  }
