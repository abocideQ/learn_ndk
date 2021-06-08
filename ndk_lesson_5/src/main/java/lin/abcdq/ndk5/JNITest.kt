package lin.abcdq.ndk5

import android.opengl.GLSurfaceView
import android.util.Log
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10

/**
 * Triangle Rectangle
 * glDrawArrays(GL_TRIANGLES, 0, 3 * 三角个数);
 * GL_TRIANGLES: 每3个顶点组成一个三角
 * GL_TRIANGLE_STRIP : 复用顶点 -> V0 V1 V2 -> V1 V2 V3 -> V2 V3 V4 依次组成顶点
 * GL_TRIANGLE_FAN ： 与GL_TRIANGLE_STRIP 相似，顶点复用方式不同
 */
class JNITest : GLSurfaceView.Renderer {

    init {
        System.loadLibrary("native_lib5")
    }

    fun setData(buffer: FloatArray, bufferSize: Int, color: Int) {
        native_OnSetData(buffer, bufferSize, color)
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

    private external fun native_OnSetData(buffer: FloatArray, bufferSize: Int, color: Int)

    private external fun native_OnSurfaceCreated()

    private external fun native_OnSurfaceChanged(w: Int, h: Int)

    private external fun native_OnDrawFrame()

    private external fun native_OnDestroy()
}