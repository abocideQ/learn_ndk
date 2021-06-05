package lin.abcdq.ndk4

import android.graphics.Color
import android.opengl.GLSurfaceView
import android.os.Build
import androidx.annotation.RequiresApi
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10

/**
 * openGLes Build
 *
 * cmake {
 *  cppFlags "-std=c++11 -frtti -fexceptions" (-std=c++1 : 支持C++11 , frtti：运行时类型识别(RTTI) , fexceptions: 开启Android端NDK异常捕获)
 *  abiFilters 'arm64-v8a', 'armeabi-v7a', 'x86', 'x86_64'
 *  }
 *
 */
@RequiresApi(Build.VERSION_CODES.CUPCAKE)
class JNITest : GLSurfaceView.Renderer {

    init {
        System.loadLibrary("native_lib4")
    }

    override fun onSurfaceCreated(gl: GL10?, config: EGLConfig?) {
        native_OnSurfaceCreated(Color.GRAY)
    }

    override fun onSurfaceChanged(gl: GL10?, width: Int, height: Int) {
        native_OnSurfaceChanged(width, height)
    }

    override fun onDrawFrame(gl: GL10?) {
        native_OnDrawFrame()
    }

    private external fun native_OnSurfaceCreated(color: Int)

    private external fun native_OnSurfaceChanged(w: Int, h: Int)

    private external fun native_OnDrawFrame()
}