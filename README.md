opengl:https://learnopengl-cn.github.io/

native 代码补全问题： android studio 4.0 + -> File -> other setting -> clangd -> code completion -> clangd completion with builtin (laji AS!)

```
Ⅰ 
CMake 简单使用
NDK 构建顺序
1.Gradle 调用您的外部构建脚本 CMakeLists.txt。
2.CMake 按照构建脚本中的命令将 C++ 源文件 xxx.cpp 编译到共享的对象库中，并命名为 xxx.so，Gradle 随后会将其打包到 APK 中。
3.运行时，应用使用 System.loadLibrary() 加载原生库。
```

```
Ⅱ 
JavaVM + JNIEnv + 静态jni注册 + 动态jni注册
静态注册：JNIEXPORT jobject 指定 返回类型 ，JNICALL 指定 函数
JavaVM 是虚拟机在 JNI 层的代表，一个进程只有一个的全局变量，所有的线程共用一个 JavaVM。
JNIEnv 表示 Java 调用 native 语言的环境，是一个封装了几乎全部 JNI 方法的指针
#if + #endif : 宏判断 ， #define ：宏定义
```

```
Ⅲ 
CMake 使用
```

```
Ⅳ 
openGLes 引入
cmake {
    cppFlags "-std=c++11 -frtti -fexceptions" (-std=c++1 : 支持C++11 , frtti：运行时类型识别(RTTI) , fexceptions: 开启Android端NDK异常捕获)
    abiFilters 'arm64-v8a', 'armeabi-v7a', 'x86', 'x86_64'
}
```

```
Ⅴ 
Triangle Rectangle
glDrawArrays(GL_TRIANGLES, 0, 3 * 三角个数);
GL_TRIANGLES: 每3个顶点组成一个三角
GL_TRIANGLE_STRIP : 复用顶点 -> V0 V1 V2 -> V1 V2 V3 -> V2 V3 V4 依次组成顶点
GL_TRIANGLE_FAN ： 与GL_TRIANGLE_STRIP 相似，顶点复用方式不同
```

```
Ⅵ 
VBO : 每个VBO对应一个float[] 相当于一个VBO对应绘制一个物体
VAO : VBO不支持切换，每个VAO绑定一个VBO，方便与后面切换绘制不同的物体
EBO : 索引:指定绘制顺序，方便矩形等形状绘制(v1 v2 v3 , v4 v5 v6 - > v1 v2 v3 , v1 v3 v4)
纹理 ：Texture
```

```
Ⅶ matrix
vecN * matrixN = new VecN
vecN * matrix1N * matrix2N = new VecN
矩阵相乘顺序 ：缩放 -> 旋转 -> 位移 , 如果先位移再缩放，位移的向量会被缩放
https://learnopengl-cn.github.io/01%20Getting%20started/07%20Transformations/
```