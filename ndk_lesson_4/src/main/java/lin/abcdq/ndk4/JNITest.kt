package lin.abcdq.ndk4

import android.content.Context
import android.graphics.Color
import android.opengl.GLSurfaceView
import android.os.Build
import androidx.annotation.RequiresApi
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10

/**
 * openGLes 背景
 */
@RequiresApi(Build.VERSION_CODES.CUPCAKE)
class JNITest : GLSurfaceView.Renderer {

    init {
        System.loadLibrary("native_lib")
    }

    override fun onSurfaceCreated(gl: GL10?, config: EGLConfig?) {
        JNISurfaceCreate(Color.GRAY)
    }

    override fun onSurfaceChanged(gl: GL10?, width: Int, height: Int) {
        JNISurfaceChange(width, height)
    }

    override fun onDrawFrame(gl: GL10?) {
        JNIOnDrawFrame()
    }

    external fun JNISurfaceCreate(color: Int)

    external fun JNISurfaceChange(w: Int, h: Int)

    external fun JNIOnDrawFrame()
}