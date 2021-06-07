#include "TriangleSample.h"
#include "../util/Log.h"

extern "C" {
const char *vertex = "#version 300 es                           \n"
                     "layout(location = 0) in vec4 vPosition;   \n"
                     "layout(location = 1) out vec4 vColor;     \n"
                     "void main(){                              \n"
                     "gl_Position = vPosition;                  \n"
                     "fColor = vColor;                          \n"
                     "}                                         \n";
const char *fragment = "version 300es                           \n"
                       "precision mediump float;                \n"
                       "out vec4 fColor;                        \n"
                       "void main(){                            \n"
                       "gl_FragColor = fColor;                  \n"
                       "}                                       \n";

void TriangleSample::onSetData(float *bufferArray, int arraySize, int color) {
    int i = 0;
    for (; i < arraySize; i = i + 1) {
        mData[i] = bufferArray[i];
    }
    GLfloat redF = ((color >> 16) & 0xFF) * 1.0f / 255;
    GLfloat greenF = ((color >> 8) & 0xFF) * 1.0f / 255;
    GLfloat blueF = (color & 0xFF) * 1.0f / 255;
    GLfloat alphaF = ((color >> 24) & 0xFF) * 1.0f / 255;
    mColor[0] = redF;
    mColor[1] = greenF;
    mColor[2] = blueF;
    mColor[3] = alphaF;
}

void TriangleSample::onChanged(int w, int h) {
    m_SurfaceWidth = w;
    m_SurfaceHeight = h;
}

void TriangleSample::onInit() {
    m_Program = GLUtils::glProgram(vertex, fragment);
}

void TriangleSample::onDraw() {
    LOGCATE("Program %d", m_Program);
    GLUtils::glClear(m_Program);
    GLUtils::glUse(m_Program);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, mData);
    glEnableVertexAttribArray(0);//location = 0 vPosition
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, mColor);
    glEnableVertexAttribArray(1);//location = 1 vColor
    glDrawArrays(GL_TRIANGLES, 0, 3);
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


