#include "CameraSample.h"
#include "../util/Log.h"

extern "C" {
float m3DBOXVertexBuffer[] = {
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f
};

const char *vertexTexture = "#version 300 es                            \n"
                            "layout(location = 0) in vec4 vPosition;    \n"
                            "layout(location = 1) in vec2 vTexCoord;    \n"
                            "out vec2 fTexCoord;                        \n"
                            "void main(){                               \n"
                            "gl_Position = vPosition;                   \n"
                            "fTexCoord = vec2(vTexCoord.x, 1.0 - vTexCoord.y);\n"
                            "}                                          \n";

const char *fragmentTexture = "#version 300 es                               \n"
                              "in vec2 fTexCoord;                            \n"
                              "uniform sampler2D texture1Map;                \n"
                              "uniform sampler2D texture2Map;                \n"
                              "layout(location = 0)out vec4 FragColor;       \n"
                              "void main(){                                  \n"//0.2: 80%第一个输入颜色 20%第二个输入颜色.
                              "FragColor = mix(texture(texture1Map, fTexCoord), texture(texture2Map, fTexCoord), 0.35);  \n"
                              "}                                             \n";

void CameraSample::onImage(uint8_t *buffer1, int size1, int w1, int h1, uint8_t *buffer2, int size2,
                           int w2, int h2) {
    m_ImageBuffer1 = buffer1;
    m_ImageSize1 = size1;
    m_ImageWidth1 = w1;
    m_ImageHeight1 = h1;
    m_ImageBuffer2 = buffer2;
    m_ImageSize2 = size2;
    m_ImageWidth2 = w2;
    m_ImageHeight2 = h2;
}

void CameraSample::onInit() {
    glGenTextures(1, &m_Texture1);
    glBindTexture(GL_TEXTURE_2D, m_Texture1);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_ImageWidth1, m_ImageHeight1, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, m_ImageBuffer1);
    glGenerateMipmap(GL_TEXTURE_2D);
    free(m_ImageBuffer1);

    glGenTextures(1, &m_Texture2);
    glBindTexture(GL_TEXTURE_2D, m_Texture2);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_ImageWidth2, m_ImageHeight2, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, m_ImageBuffer2);
    glGenerateMipmap(GL_TEXTURE_2D);
    free(m_ImageBuffer2);

    m_Program = GLUtils::glProgram(vertexTexture, fragmentTexture);
    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);
    glGenBuffers(1, &m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(m3DBOXVertexBuffer), m3DBOXVertexBuffer, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float_t), (void *) 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                          (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void CameraSample::onChanged(int w, int h) {
    glViewport(0, 0, w, h);
}

void CameraSample::onDraw() {
    if (m_Program == GL_NONE) return;
    glClear(GL_STENCIL_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glUseProgram(m_Program);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_Texture1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, m_Texture2);
    GLint tex1Map = glGetUniformLocation(m_Program, "texture1Map");
    GLint tex2Map = glGetUniformLocation(m_Program, "texture2Map");
    glUniform1i(tex1Map, 0);
    glUniform1i(tex2Map, 1);
    glBindVertexArray(m_VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void CameraSample::onDestroy() {

}

CameraSample *CameraSample::mSample = nullptr;
CameraSample *CameraSample::instance() {
    if (mSample == nullptr) mSample = new CameraSample();
    return mSample;
}
}

