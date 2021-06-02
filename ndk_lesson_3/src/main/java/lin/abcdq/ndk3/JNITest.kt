package lin.abcdq.ndk3

import android.content.Context
import android.widget.Toast
/**
 *  CMake
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