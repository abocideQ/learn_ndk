#include "TextureSample.h"
#include "../util/Log.h"

extern "C" {

//const char *vertex = "#version 300 es                            \n"
//                     "layout(location = 0) in vec4 vPosition;    \n"
//                     "layout(location = 1) in vec4 vColor;       \n"
//                     "out vec4 fColor;                           \n"
//                     "layout(location = 2) in vec2 vTexCoord;    \n"
//                     "out vec2 fTexCoord;                        \n"
//                     "void main(){                               \n"
//                     "gl_Position = vPosition;                   \n"
//                     "fColor = vColor;                           \n"
//                     "}                                          \n";
//
//
//const char *fragment = "#version 300 es                               \n"
//                       "precision mediump float;                      \n"
//                       "in vec4 fColor;                               \n"
//                       "out vec4 fragColor;                           \n"
//                       "uniform sampler2D s_TextureMap;               \n"
//                       "in vec2 fTexCoord;                            \n"
//                       "layout(location = 0) out vec4 fTex;           \n"
//                       "void main(){                                  \n"
//                       "fragColor = fColor;                           \n"
//                       "fTex = texture(s_TextureMap, ePosition);      \n"
//                       // s_TextureMap ：采样器, texture() 为内置的采样函数，ePosition 为顶点着色器传进来的纹理坐标
//                       // 根据纹理坐标对纹理进行采样，输出采样的 rgba 值（4维向量）
//                       "}                                             \n";
//
//GLfloat vertexBuffer[] = {
//        -1.0f, 0.5f, 0.0f,
//        -1.0f, -0.5f, 0.0f,
//        1.0f, -0.5f, 0.0f,
//        1.0f, 0.5f, 0.0f,
//};
//
//GLfloat textureBuffer[] = {
//        0.0f, 0.0f,
//        0.0f, 1.0f,
//        1.0f, 1.0f,
//        1.0f, 0.0f
//};
//
//void TextureSample::onSetData(float *bufferArray, int arraySize, int color) {
//    mDataSize = arraySize;
//    mData = new float[mDataSize];
//    int i = 0;
//    for (; i < mDataSize; i = i + 1) {
//        mData[i] = bufferArray[i];
//    }
//    GLfloat redF = ((color >> 16) & 0xFF) * 1.0f / 255;
//    GLfloat greenF = ((color >> 8) & 0xFF) * 1.0f / 255;
//    GLfloat blueF = (color & 0xFF) * 1.0f / 255;
//    GLfloat alphaF = ((color >> 24) & 0xFF) * 1.0f / 255;
//    mColorSize = arraySize / 3 * 4;
//    mColor = new float[mColorSize];
//    i = 0;
//    for (; i < mColorSize; i = i + 4) {
//        mColor[i + 0] = redF - ((float) i * 0.005f);
//        mColor[i + 1] = greenF + ((float) i * 0.005f);
//        mColor[i + 2] = blueF + ((float) i * 0.005f);
//        mColor[i + 3] = alphaF - ((float) i * 0.005f);
//    }
//}
//
//void TextureSample::onInit() {
//    glGenTextures(1, &m_Texture);//生成纹理
//    glBindTexture(GL_TEXTURE_2D, m_Texture);//绑定纹理
//    //设置纹理 S/T 轴（横轴）的拉伸方式为截取
//    //GL_REPEAT： 默认方案，重复纹理图片。
//    //GL_MIRRORED_REPEAT：类似于默认方案，不过每次重复的时候进行镜像重复。
//    //GL_CLAMP_TP_EDGE：将坐标限制在0到1之间。超出的坐标会重复绘制边缘的像素，变成一种扩展边缘的图案
//    //GL_CLAMP_TO_BORDER：超出的坐标将会被绘制成用户指定的边界颜色。
//    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//    //设置放大、缩小时的纹理过滤方式，必须设定，否则纹理全黑
//    //GL_NEAREST 最近点过滤，指的是纹理坐标最靠近哪个纹素，就用哪个纹素，速度最快，效果最差
//    //GL_LINEAR 线性过滤，纹理坐标位置附近的几个纹素值进行某种插值计算之后的结果，效果一般，速度较快。
//    //GL_TEXTURE_MIN_FILTER GL_TEXTURE_MAG_FILTER 缩小时 放大时
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    //glGenerateMipmaps 获取mipmaps（每一张纹理图的大小都是前一张的1/4，直到剩最后一个像素为止）
//    glBindTexture(GL_TEXTURE_2D, GL_NONE);
//    m_Program = GLUtils::glProgram(vertex, fragment);
//    if (m_Program) {
//        //s_TextureMap
//        m_TexMap = glGetUniformLocation(m_Program, "s_TextureMap");
//    } else {
//        LOGCATE("program create failed");
//    }
//}
//
//void TextureSample::onChanged(int w, int h) {
//    m_SurfaceWidth = w;
//    m_SurfaceHeight = h;
//    glViewport(0, 0, m_SurfaceWidth, m_SurfaceHeight);
//}
//
//void TextureSample::onDraw() {
//    if (m_Program == GL_NONE || m_Texture == GL_NONE) return;
//    glUseProgram(m_Program);
//    //stride: 3 * sizeof(GLfloat):  顶点属性组之间的间隔,当顶点属性紧密排列时，可以填0，由OpenGL代替我们计算出该值,一个顶点占有的总的字节数
//    //pointer：当前指针指向的vertex内部的偏离字节数，可以唯一的标识顶点某个属性的偏移量
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), vertexBuffer);
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), mColor);
//    glEnableVertexAttribArray(1);
//    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), textureBuffer);
//    glEnableVertexAttribArray(2);
//    //上传图片
//    glActiveTexture(GL_TEXTURE0);
//    glBindTexture(GL_TEXTURE_2D, m_Texture);
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
//    glBindTexture(GL_TEXTURE_2D, GL_NONE);
//    //激活纹理 纹理ID
//    glActiveTexture(GL_TEXTURE0);
//    glBindTexture(GL_TEXTURE_2D, m_Texture);
//    //对纹理采样器变量进行设置 v0：纹理层
//    glUniform1i(m_TexMap, 0);
//    GLushort indices[] = {0, 1, 2, 0, 2, 3};// 元素索引数组，按照指定的索引顺序绘制，复用。
//    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
//}
//
//void TextureSample::onDestroy() {
//    GLUtils::glProgramDel(m_Program);
//    m_Program = GL_NONE;
//    if (mSample) {
//        delete mSample;
//        mSample = nullptr;
//    }
//}
//
//TextureSample *TextureSample::mSample = nullptr;
//
//TextureSample *TextureSample::instance() {
//    if (mSample == nullptr) mSample = new TextureSample();
//    return mSample;
//}
}


