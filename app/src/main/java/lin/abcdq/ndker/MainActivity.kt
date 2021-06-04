package lin.abcdq.ndker

import android.opengl.GLSurfaceView
import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import lin.abcdq.ndk4.JNITest

//https://blog.csdn.net/afei__/article/details/81290711

class MainActivity : AppCompatActivity() {
    private lateinit var mGLSurfaceView: GLSurfaceView
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        mGLSurfaceView = findViewById(R.id.gsv_content)
        mGLSurfaceView.setEGLContextClientVersion(3)
        mGLSurfaceView.setRenderer(JNITest())
    }
}