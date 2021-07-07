opengl:https://learnopengl-cn.github.io/
![Image text](https://github.com/ABCDQ123/ndktest/blob/main/app/image/ndker.gif)
native 代码补全问题： android studio 4.0 + -> File -> other setting -> clangd -> code completion -> clangd completion with builtin
```
Ⅰ 
CMake 简单使用
NDK 构建顺序
1.Gradle 调用您的外部构建脚本 CMakeLists.txt。
2.CMake 按照构建脚本中的命令将 C++ 源文件 xxx.cpp 编译到共享的对象库中，并命名为 xxx.so，Gradle 随后会将其打包到 APK 中。
3.运行时，应用使用 System.loadLibrary() 加载原生库。
```

```
Ⅱ 
JavaVM + JNIEnv + 静态jni注册 + 动态jni注册
静态注册：JNIEXPORT jobject 指定 返回类型 ，JNICALL 指定 函数
JavaVM 是虚拟机在 JNI 层的代表，一个进程只有一个的全局变量，所有的线程共用一个 JavaVM。
JNIEnv 表示 Java 调用 native 语言的环境，是一个封装了几乎全部 JNI 方法的指针
#if + #endif : 宏判断 ， #define ：宏定义
```

```
Ⅲ 
CMake 使用
```

```
Ⅳ 
openGLes 引入
cmake {
    cppFlags "-std=c++11 -frtti -fexceptions" (-std=c++1 : 支持C++11 , frtti：运行时类型识别(RTTI) , fexceptions: 开启Android端NDK异常捕获)
    abiFilters 'arm64-v8a', 'armeabi-v7a', 'x86', 'x86_64'
}
```

```
Ⅴ 
Triangle Rectangle
glDrawArrays(GL_TRIANGLES, 0, 3 * 三角个数);
GL_TRIANGLES: 每3个顶点组成一个三角
GL_TRIANGLE_STRIP : 复用顶点 -> V0 V1 V2 -> V1 V2 V3 -> V2 V3 V4 依次组成顶点
GL_TRIANGLE_FAN ： 与GL_TRIANGLE_STRIP 相似，顶点复用方式不同
```

```
Ⅵ 
VBO : 每个VBO对应一个float[] 相当于一个VBO对应绘制一个物体
VAO : VBO不支持切换，每个VAO绑定一个VBO，方便与后面切换绘制不同的物体
EBO : 索引:指定绘制顺序，方便矩形等形状绘制(v1 v2 v3 , v4 v5 v6 - > v1 v2 v3 , v1 v3 v4)
纹理 ：Texture
```

```
Ⅶ matrix
vecN * matrixN = new VecN
vecN * matrix1N * matrix2N = new VecN
矩阵相乘顺序 ：缩放 -> 旋转 -> 位移 , 如果先位移再缩放，位移的向量会被缩放
https://learnopengl-cn.github.io/01%20Getting%20started/07%20Transformations/
```
```
Ⅷ
glm: 矩阵库
model: 模型矩阵：世界空间/坐标（世界）
view: 视图矩阵：观察空间/坐标（摄像头）
projection: 投影矩阵：裁剪空间
lookAt: 摄像头
https://learnopengl-cn.github.io/01%20Getting%20started/08%20Coordinate%20Systems/
https://learnopengl-cn.github.io/01%20Getting%20started/09%20Camera/

fbo: 离屏渲染

egl:
Display(EGLDisplay) 显示设备
Surface（EGLSurface）存储图像的内存区域,Color Buffer颜色缓冲区, Stencil Buffer模板缓冲区, Depth Buffer深度缓冲区
Context (EGLContext) OpenGL ES 绘图状态信息
```
```
YUV（亮度 色度 浓度） : 
Y/U/V/R/G/B -> 取值范围0~255
NV21/NV12 (YUV420sp) : 
 -> YYYY + VU / YYYY + UV;
 -> char *y = data; char *uv = y + w * h;
 -> ySize = w * h; uSize = w * h / 4; vSzie = uSize; 
YV12/I420 (YUV420p) : 
 -> YYYY + V + U / YYYY + U + V;
 -> char *y = data; char *v = y + w * h; char *u = y + w * h + (w * h) / 4;
 -> ySize = w * h; uSize = w * h / 4; vSzie = uSize; 
YUV422 (YUV422) :  -> YYYY VV UU
YUV422 (YUVY)   ： -> YUYV
YUV422 (UYVY)   ： -> UYVY
YUV444 (YUV444p)： -> Y V U
---------------------------------------------------
NV21 旋转： 
Y00  Y01  Y02  Y03              Y30  Y20  Y10  Y00
Y10  Y11  Y12  Y13    旋转90度   Y31  Y21  Y11  Y01
Y20  Y21  Y22  Y23    ----->    Y32  Y22  Y12  Y02
Y30  Y31  Y32  Y33              Y33  Y23  Y13  Y03
                      
V00  U00  V01  U01    旋转90度    V10  U10  V00  U00
V10  U10  V11  U11    ----->     V11  U11  V01  U01
---------------------------------------------------
NV21 缩放（横纵同时放大缩小）：
               Y00 Y00 Y01 Y01
Y00  Y01       Y00 Y00 Y01 Y01
Y02  Y03       Y02 Y02 Y03 Y03       
               Y02 Y02 Y03 Y03              
                
U00  U00       U00 U00 U00 U00       
               U00 U00 U00 U00  
---------------------------------------------------
NV21 裁剪：
Y00  Y01       Y02  Y03 
Y02  Y03

U00  U00       U00
---------------------------------------------------
NV21(YUV420sp) -> RGB
in vec2 v_texCoord; 
layout(location = 0) out vec4 v_texCoord;
uniform sampler2D y_texture;                        
uniform sampler2D uv_texture; 
void main(){
vec3 yuv;
//We had put the Y values of each pixel to the R,G,B components by
//GL_LUMINANCE, that's why we're pulling it from the R component,
//glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, w, h, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, yBuffer);
//we could also use G or B
yuv.x = texture(y_texture, v_texCoord).r;   
//We had put the U and V values of each pixel to the A and R,G,B
//components of the texture respectively using GL_LUMINANCE_ALPHA.
//glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE_ALPHA, w / 2, h / 2, 0, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, uvBuffer);
//Since U,V bytes are interspread in the texture, this is probably
//the fastest way to use them in the shader
//Y/U/V/R/G/B -> 0~255 -> in the shader need be -0.5~0.5 -> texture(yuv, texCoord).r-0.5
yuv.y = texture(uv_texture, v_texCoord).a-0.5;  
yuv.z = texture(uv_texture, v_texCoord).r-0.5;  
(
1.0f,    1.0f,     1.0f,                    
0.0f,    -0.344f,  1.770f,                  
1.403f,  -0.714f,  0.0f
) * yuv;
outColor = vec4(rgb, 1);
}

 ->
        vec4 NV21toRGB(vec2 texCoord) {
                    float y = 0.0f;
                    float u = 0.0f;
                    float v = 0.0f;
                    float r = 0.0f;
                    float g = 0.0f;
                    float b = 0.0f;
                    y = texture(s_textureY, texCoord).r;
                    u = texture(s_textureVU, texCoord).a;
                    v = texture(s_textureVU, texCoord).r;
                    u = u - 0.5;
                    v = v - 0.5;
                    r = y + 1.403 * v;
                    g = y - 0.344 * u - 0.714 * v;
                    b = y + 1.770 * u;
                    return vec4(r, g, b, 1.0f);
                }   
---------------------------------------------------
YUV420888 -> RGB
in vec2 v_texCoord; 
layout(location = 0) out vec4 v_texCoord;
uniform sampler2D y_texture;                        
uniform sampler2D u_texture; 
uniform sampler2D v_texture; 
void main(){
vec3 yuv;
//glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, w, h, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, yBuffer);
yuv.x = texture(y_texture, v_texCoord).r;   
//glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, w/2, h/2, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, uBuffer);
yuv.y = texture(u_texture, v_texCoord).r-0.5;  
//glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, w/2, h/2, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, vBuffer);
yuv.z = texture(v_texture, v_texCoord).r-0.5;  
(
1.0f,    1.0f,     1.0f,                    
0.0f,    -0.344f,  1.770f,                  
1.403f,  -0.714f,  0.0f
) * yuv;
outColor = vec4(rgb, 1);
}
 ->
 vec4 YUV420888toRGB(vec2 texCoord) {
                    float y = 0.0f;
                    float u = 0.0f;
                    float v = 0.0f;
                    float r = 0.0f;
                    float g = 0.0f;
                    float b = 0.0f;
                    y = texture(s_textureY, texCoord).r;
                    u = texture(s_textureU, texCoord).r;
                    v = texture(s_textureV, texCoord).r;
                    u = u - 0.5;
                    v = v - 0.5;
                    r = y + 1.403 * v;
                    g = y - 0.344 * u - 0.714 * v;
                    b = y + 1.770 * u;
                    return vec4(r, g, b, 1.0f);
                }
---------------------------------------------------
RGB24 -> YUV420P
Y= 0.299*R+0.587*G+0.114*B
U=-0.147*R-0.289*G+0.463*B
V= 0.615*R-0.515*G-0.100*B
```