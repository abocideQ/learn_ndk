package lin.abcdq.ndk8

import android.opengl.GLSurfaceView
import android.util.Log
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10

/**
 * 坐标
 * 摄像机
 */
class JNITest : GLSurfaceView.Renderer {

    init {
        System.loadLibrary("native_lib8")
    }

    fun onImageUpdate(
        buffer1: ByteArray,
        size1: Int,
        w1: Int,
        h1: Int,
        buffer2: ByteArray,
        size2: Int,
        w2: Int,
        h2: Int
    ) {
        native_onImageUpdate(buffer1, size1, w1, h1, buffer2, size2, w2, h2)
    }

    override fun onSurfaceCreated(gl: GL10?, config: EGLConfig?) {
        native_OnSurfaceCreated()
    }

    override fun onSurfaceChanged(gl: GL10?, width: Int, height: Int) {
        native_OnSurfaceChanged(width, height)
    }

    override fun onDrawFrame(gl: GL10?) {
        native_OnDrawFrame()
    }

    fun onDestroy() {
        native_OnDestroy()
    }

    private external fun native_onImageUpdate(
        buffer1: ByteArray,
        size1: Int,
        w1: Int,
        h1: Int,
        buffer2: ByteArray,
        size2: Int,
        w2: Int,
        h2: Int
    )

    private external fun native_OnSurfaceCreated()

    private external fun native_OnSurfaceChanged(w: Int, h: Int)

    private external fun native_OnDrawFrame()

    private external fun native_OnDestroy()
}