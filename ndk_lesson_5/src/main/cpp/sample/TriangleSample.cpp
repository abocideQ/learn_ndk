#include "TriangleSample.h"
#include "../util/Log.h"

extern "C" {

const char *vertex = "#version 300 es                           \n"
                     "layout(location = 0) in vec4 vPosition;   \n"
                     "layout(location = 1) in vec4 vColor;      \n"
                     "out vec4 fColor;                          \n"
                     "void main(){                              \n"
                     "gl_Position = vPosition;                  \n"
                     "fColor = vColor;                          \n"
                     "}                                         \n";

const char *fragment = "#version 300 es                         \n"
                       "precision mediump float;                \n"
                       "in vec4 fColor;                         \n"
                       "out vec4 fragColor;                     \n"
                       "void main(){                            \n"
                       "fragColor = fColor;                     \n"
                       "}                                       \n";

//const GLfloat TRIANGLE_VERTICES[] = {0.0f, 0.5f, 0.0f,
//                                     -0.5f, -0.5f, 0.0f,
//                                     0.5f, -0.5f, 0.0f};
//
//float color[] = {
//        0.0f, 1.0f, 0.0f, 1.0f,
//        1.0f, 0.0f, 0.0f, 1.0f,
//        0.0f, 0.0f, 1.0f, 1.0f
//};

void TriangleSample::onSetData(float *bufferArray, int arraySize, int color) {
    mData = new float[arraySize];
    int i = 0;
    for (; i < arraySize; i = i + 1) {
        mData[i] = bufferArray[i];
    }
    GLfloat redF = ((color >> 16) & 0xFF) * 1.0f / 255;
    GLfloat greenF = ((color >> 8) & 0xFF) * 1.0f / 255;
    GLfloat blueF = (color & 0xFF) * 1.0f / 255;
    GLfloat alphaF = ((color >> 24) & 0xFF) * 1.0f / 255;
    mColor = new float[arraySize / 3 * 4];
    i = 0;
    for (; i < arraySize; i = i + 4) {
        mColor[i + 0] = redF;
        mColor[i + 1] = greenF;
        mColor[i + 2] = blueF;
        mColor[i + 3] = alphaF;
    }

}

void TriangleSample::onInit() {
    m_Program = GLUtils::glProgram(vertex, fragment);
}

void TriangleSample::onChanged(int w, int h) {
    m_SurfaceWidth = w;
    m_SurfaceHeight = h;
    GLUtils::glProgramViewPort(m_SurfaceWidth, m_SurfaceHeight);
}

void TriangleSample::onDraw() {
    GLUtils::glProgramClear(m_Program);
    GLUtils::glProgramUse(m_Program);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, mData);
    glEnableVertexAttribArray(0);//location = 0 vPosition
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, mColor);
    glEnableVertexAttribArray(1);//location = 1 vColor
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glUseProgram(GL_NONE);
}

void TriangleSample::onDestroy() {
    GLUtils::glProgramDel(m_Program);
    m_Program = GL_NONE;
    if (mSample) {
        delete mSample;
        mSample = nullptr;
    }
}

TriangleSample *TriangleSample::mSample = nullptr;

TriangleSample *TriangleSample::instance() {
    if (mSample == nullptr) mSample = new TriangleSample();
    return mSample;
}
}


