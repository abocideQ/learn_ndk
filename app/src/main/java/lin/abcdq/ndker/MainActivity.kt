package lin.abcdq.ndker

import android.graphics.BitmapFactory
import android.graphics.Color
import android.opengl.GLSurfaceView
import android.os.Bundle
import android.view.View
import android.widget.RelativeLayout
import androidx.appcompat.app.AppCompatActivity
import java.nio.ByteBuffer

class MainActivity : AppCompatActivity() {

    //    private val mRender = lin.abcdq.ndk1.JNITest()
//    private val mRender = lin.abcdq.ndk2.JNITest()
//    private val mRender = lin.abcdq.ndk3.JNITest()
//    private val mRender = lin.abcdq.ndk4.JNITest()
//    private val mRender = lin.abcdq.ndk5.JNITest()
//    private val mRender = lin.abcdq.ndk6.JNITest()
    private val mRender = lin.abcdq.ndk7.JNITest()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        bitmap()
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

    private fun bitmap() {
        val bitmap = BitmapFactory.decodeResource(resources, R.drawable.java)
        val length: Int = bitmap.byteCount
        val buffer: ByteBuffer = ByteBuffer.allocate(length)
        bitmap.copyPixelsToBuffer(buffer)
        val bytes = buffer.array()
        mRender.onImageUpdate(bytes, bytes.size, bitmap.width, bitmap.height)
    }

    private val m3dBoxBuffer = floatArrayOf(
        //背面矩形
        0.75f, 0.75f, 0.0f,
        -0.25f, 0.75f, 0.0f,
        -0.25f, -0.25f, 0.0f,
        0.75f, 0.75f, 0.0f,
        -0.25f, -0.25f, 0.0f,
        0.75f, -0.25f, 0.0f,
        //左侧矩形
        -0.25f, 0.75f, 0.0f,
        -0.75f, 0.25f, 0.0f,
        -0.75f, -0.75f, 0.0f,
        -0.25f, 0.75f, 0.0f,
        -0.75f, -0.75f, 0.0f,
        -0.25f, -0.25f, 0.0f,
        //底部矩形
        0.75f, -0.25f, 0.0f,
        -0.25f, -0.25f, 0.0f,
        -0.75f, -0.75f, 0.0f,
        0.75f, -0.25f, 0.0f,
        -0.75f, -0.75f, 0.0f,
        0.25f, -0.75f, 0.0f,
        //正面矩形
        0.25f, 0.25f, 0.0f,
        -0.75f, 0.25f, 0.0f,
        -0.75f, -0.75f, 0.0f,
        0.25f, 0.25f, 0.0f,
        -0.75f, -0.75f, 0.0f,
        0.25f, -0.75f, 0.0f,
        //右侧矩形
        0.75f, 0.75f, 0.0f,
        0.25f, 0.25f, 0.0f,
        0.25f, -0.75f, 0.0f,
        0.75f, 0.75f, 0.0f,
        0.25f, -0.75f, 0.0f,
        0.75f, -0.25f, 0.0f,
        //顶部矩形
        0.75f, 0.75f, 0.0f,
        -0.25f, 0.75f, 0.0f,
        -0.75f, 0.25f, 0.0f,
        0.75f, 0.75f, 0.0f,
        -0.75f, 0.25f, 0.0f,
        0.25f, 0.25f, 0.0f
    )

    private val mRectangleBuffer = floatArrayOf(
        -0.5f, 0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
    )
    private val mTriangleBuffer = floatArrayOf(
        0.0f, 0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
    )
    private var mColor = Color.RED
}