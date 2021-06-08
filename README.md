# native 代码补全问题： android studio 4.0 + -> File -> other setting -> clangd -> code completion -> clangd completion with builtin (laji AS!)
les1
```
CMake 简单使用
NDK 构建顺序
1.Gradle 调用您的外部构建脚本 CMakeLists.txt。
2.CMake 按照构建脚本中的命令将 C++ 源文件 xxx.cpp 编译到共享的对象库中，并命名为 xxx.so，Gradle 随后会将其打包到 APK 中。
3.运行时，应用使用 System.loadLibrary() 加载原生库。
```
les2
```
JavaVM + JNIEnv + 静态jni注册 + 动态jni注册
静态注册：JNIEXPORT jobject 指定 返回类型 ，JNICALL 指定 函数
JavaVM 是虚拟机在 JNI 层的代表，一个进程只有一个的全局变量，所有的线程共用一个 JavaVM。
JNIEnv 表示 Java 调用 native 语言的环境，是一个封装了几乎全部 JNI 方法的指针
#if + #endif : 宏判断 ， #define ：宏定义
```
les3
```
CMake 使用
```
les4
```
openGLes 引入
cmake {
    cppFlags "-std=c++11 -frtti -fexceptions" (-std=c++1 : 支持C++11 , frtti：运行时类型识别(RTTI) , fexceptions: 开启Android端NDK异常捕获)
    abiFilters 'arm64-v8a', 'armeabi-v7a', 'x86', 'x86_64'
}
```
les5
```
Triangle Rectangle
glDrawArrays(GL_TRIANGLES, 0, 3 * 三角个数);
GL_TRIANGLES: 每3个顶点组成一个三角
GL_TRIANGLE_STRIP : 复用顶点 -> V0 V1 V2 -> V1 V2 V3 -> V2 V3 V4 依次组成顶点
GL_TRIANGLE_FAN ： 与GL_TRIANGLE_STRIP 相似，顶点复用方式不同
```