package lin.abcdq.ndk1

import android.content.Context
import android.widget.Toast

/**
 *  简单NDK使用
 *  ===================NDK 步骤
 *  1.Gradle 调用您的外部构建脚本 CMakeLists.txt。
 *  2.CMake 按照构建脚本中的命令将 C++ 源文件 xxx.cpp 编译到共享的对象库中，并命名为 xxx.so，Gradle 随后会将其打包到 APK 中。
 *  3.运行时，应用使用 System.loadLibrary() 加载原生库。
 */
class JNITest {

    companion object {
        fun jniString(context: Context) {
            Toast.makeText(context, "${JNITest().JNIString()}", Toast.LENGTH_SHORT).show()
        }
    }

    init {
        System.loadLibrary("native_lib")
    }

    external fun JNIString(): String?
}