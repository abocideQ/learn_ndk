#lesson 1
```
 *  CMake simple
 *  NDK
 *  1.Gradle 调用您的外部构建脚本 CMakeLists.txt。
 *  2.CMake 按照构建脚本中的命令将 C++ 源文件 xxx.cpp 编译到共享的对象库中，并命名为 xxx.so，Gradle 随后会将其打包到 APK 中。
 *  3.运行时，应用使用 System.loadLibrary() 加载原生库。
```
#lesson 2
```
 *  JavaVM + JNIEnv + 静态jni注册 + 动态jni注册
 *  静态注册：JNIEXPORT jobject 指定 返回类型 ，JNICALL 指定 函数
 *  JavaVM 是虚拟机在 JNI 层的代表，一个进程只有一个的全局变量，所有的线程共用一个 JavaVM。
 *  JNIEnv 表示 Java 调用 native 语言的环境，是一个封装了几乎全部 JNI 方法的指针
 *  #if + #endif : 宏判断 ， #define ：宏定义
```
#lesson 3
```
 *  CMake
```
