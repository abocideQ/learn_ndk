package lin.abcdq.ndker

import android.graphics.Color
import android.opengl.GLSurfaceView
import android.os.Bundle
import android.view.View
import android.widget.RelativeLayout
import androidx.appcompat.app.AppCompatActivity


class MainActivity : AppCompatActivity() {
    private var mRectangleBuffer = floatArrayOf(
        -0.5f, 0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
    )
    private var mTriangleBuffer = floatArrayOf(
        0.0f, 0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
    )
    private var mColor = Color.RED
    private val mRender = lin.abcdq.ndk5.JNITest()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        mRender.setData(mRectangleBuffer, mRectangleBuffer.size, mColor)
//        mRender.setData(mTriangleBuffer, mTriangleBuffer.size, mColor)
        val mGLSurfaceView = findViewById<GLSurfaceView>(R.id.gsv_content)
        mGLSurfaceView.setEGLContextClientVersion(3)
        mGLSurfaceView.setRenderer(mRender)
        resize(mGLSurfaceView)
    }

    override fun onDestroy() {
        super.onDestroy()
        mRender.onDestroy()
    }

    private fun resize(view: View) {
        val size = resources.displayMetrics.widthPixels
        val layoutParams = view.layoutParams as RelativeLayout.LayoutParams
        layoutParams.height = size
        view.layoutParams = layoutParams
    }
}