package lin.abcdq.ndk2

import android.content.Context
import android.widget.Toast
/**
 *  JavaVM + JNIEnv + 静态jni注册 + 动态jni注册
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