cmake_minimum_required(VERSION 3.10.2)#指定 Cmake 需要的最低版本
# 创建和命名该库，第一个参数是库的名字，例如取名为 native-lib，将会生成一个命名为 libnative-lib.so 的库。
# 第二个参数是指定库的类型，一般为 SHARED，即动态库（以 .so 为后缀），还有一种是静态库 STATIC，即静态库（以 .a 为后缀）。
# 第三个参数是指定该库使用的源文件路径。
#=====================================================================
# 使用多个 add_library() 命令，您可以为 CMake 定义要从其他源文件构建的更多库。
add_library( # Sets the name of the library.
        native_lib1
        # Sets the library as a shared library.
        SHARED
        # Provides a relative path to your source file(s).
        src/main/jni/native_lib.cpp)

# 找到一个 NDK 的库，并且将这个库的路径存储在一个变量中。
# 例如上例中是找到 NDK 中的 log 库（Android 特定的日志支持库），
# 并将其路径存储在 “log-lib” 变量中，在后面你就可以通过 “${log-lib}” 命令取出变量中的值了。
find_library( # Sets the name of the path variable.
        log_lib
        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log)

# 关联库。将指定的库关联起来 。
target_link_libraries( # Specifies the target library.
        native_lib1
        # Links the target library to the log library
        # included in the NDK.
        ${log_lib})

#===================NDK 步骤
# 1.Gradle 调用您的外部构建脚本 CMakeLists.txt。
# 2.CMake 按照构建脚本中的命令将 C++ 源文件 xxx.cpp 编译到共享的对象库中，并命名为 xxx.so，Gradle 随后会将其打包到 APK 中。
# 3.运行时，应用使用 System.loadLibrary() 加载原生库。