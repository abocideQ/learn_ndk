package lin.abcdq.ndk4

import android.content.Context
import android.widget.Toast

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