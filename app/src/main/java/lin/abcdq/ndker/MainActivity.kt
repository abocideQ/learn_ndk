package lin.abcdq.ndker

import android.graphics.Color
import android.opengl.GLSurfaceView
import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity

class MainActivity : AppCompatActivity() {

    private var mBuffer = floatArrayOf(
        0.0f, 0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
    )
    private var mColor = Color.RED
    private val mRender = lin.abcdq.ndk5.JNITest()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        mRender.setData(mBuffer, mBuffer.size, mColor)
        val mGLSurfaceView = findViewById<GLSurfaceView>(R.id.gsv_content)
        mGLSurfaceView.setEGLContextClientVersion(3)
        mGLSurfaceView.setRenderer(mRender)
    }

    override fun onDestroy() {
        super.onDestroy()
        mRender.onDestroy()
    }
}