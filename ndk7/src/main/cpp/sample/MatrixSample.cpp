#include "MatrixSample.h"

extern "C" {
//!!!!矩阵相乘顺序 ：缩放 -> 旋转 -> 位移 , 如果先位移再缩放，位移的向量会被缩放
const char *vertexMatrix = "#version 300 es                            \n"
                           "layout(location = 0) in vec4 vPosition;    \n"
                           "layout(location = 1) in vec2 vTexCoord;    \n"
                           "mat4 vMatTransition = mat4(                \n"
                           " 1,  0,  0,  0.5,                          \n"
                           " 0,  1,  0,  0.5,                          \n"
                           " 0,  0,  1,  0.5,                          \n"
                           " 0,  0,  0,  1                             \n"
                           ");                                         \n"
                           "mat4 vMatScale = mat4(                     \n"
                           " 0.5,    0,    0,  0,                      \n"
                           "   0,  0.5,    0,  0,                      \n"
                           "   0,    0,  0.5,  0,                      \n"
                           "   0,    0,    0,  1                       \n"
                           ");                                         \n"
                           "out vec2 fTexCoord;                        \n"
                           "void main(){                               \n"
//                           "gl_Position = vPosition;                   \n"
//                           "gl_Position = vPosition * vMatTransition;  \n"
//                           "gl_Position = vPosition * vMatScale;       \n"
                           "gl_Position = vPosition * vMatScale * vMatTransition;\n"
                           "fTexCoord = vTexCoord;                     \n"
                           "}                                          \n";

const char *fragmentMatrix = "#version 300 es                               \n"
                             "in vec2 fTexCoord;                            \n"
                             "uniform sampler2D textureMap;                 \n"
                             "layout(location = 0)out vec4 fragColor;       \n"
                             "void main(){                                  \n"
                             "fragColor = texture(textureMap, fTexCoord);   \n"
                             "}                                             \n";

float verticesTexture[] = {
//     ---- 位置(3) ----  - 纹理坐标(2) -
        0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.0f, 0.0f, 1.0f
};
unsigned int indicesTexture[] = {
        0, 1, 3,
        1, 2, 3
};

void MatrixSample::onImage(uint8_t *buffer, int size, int w, int h) {
    m_buffer = buffer;
    m_size = size;
    m_w = w;
    m_h = h;
}

void MatrixSample::onInit() {
    glGenTextures(1, &m_Texture);
    glBindTexture(GL_TEXTURE_2D, m_Texture);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_w, m_h, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_buffer);
    glGenerateMipmap(GL_TEXTURE_2D);
    free(m_buffer);

    m_Program = GLUtils::glProgram(vertexMatrix, fragmentMatrix);
    glGenBuffers(1, &m_VAO);
    glBindVertexArray(m_VAO);
    glGenBuffers(1, &m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesTexture), verticesTexture, GL_STATIC_DRAW);
    glGenBuffers(1, &m_EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesTexture), indicesTexture, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),(void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    GLint mTexMap = glGetUniformLocation(m_Program, "textureMap");
    glUniform1i(mTexMap, 0);
}

void MatrixSample::onChanged(int w, int h) {
    glViewport(0, 0, w, h);
}

void MatrixSample::onDraw() {
    if (m_Program == GL_NONE) return;
    glClear(GL_STENCIL_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glUseProgram(m_Program);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_Texture);
    glBindVertexArray(m_VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void MatrixSample::onDestroy() {

}

MatrixSample *MatrixSample::mSample = nullptr;

MatrixSample *MatrixSample::instance() {
    if (mSample == nullptr) mSample = new MatrixSample();
    return mSample;
}
}