#include "TextureSample.h"
#include "../util/Log.h"

extern "C" {

const char *vertexTexture = "#version 300 es                            \n"
                            "layout(location = 0) in vec4 vPosition;    \n"
                            "layout(location = 1) in vec3 vColor;       \n"
                            "layout(location = 2) in vec2 vTexCoord;    \n"
                            "out vec3 fColor;                           \n"
                            "out vec2 fTexCoord;                        \n"
                            "void main(){                               \n"
                            "gl_Position = vPosition;                   \n"
                            "fColor = vColor;                           \n"
                            "fTexCoord = vTexCoord;                     \n"
                            "}                                          \n";

const char *fragmentTexture = "#version 300 es                               \n"
                              "in vec3 fColor;                               \n"
                              "in vec2 fTexCoord;                            \n"
                              "uniform sampler2D texture1Map;                \n"
                              "layout(location = 0)out vec4 FragColor;       \n"
                              "void main(){                                  \n"
                              "FragColor = texture(texture1Map, fTexCoord);  \n"
                              "}                                             \n";

float verticesTexture[] = {
//     ---- 位置(3) ----   ---- 颜色(3) ---- - 纹理坐标(2) -
        0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,   // 右上
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,   // 右下
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,   // 左下
        -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f    // 左上
};
unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
};
void TextureSample::onImage(uint8_t *buffer, int size, int w, int h) {
    m_buffer = buffer;
    m_size = size;
    m_w = w;
    m_h = h;
}

void TextureSample::onInit() {
    //创建纹理
    glGenTextures(1, &m_Texture);//生成纹理，纹理数量+纹理数组
    glBindTexture(GL_TEXTURE_2D, m_Texture);//绑定2D纹理
    // 为当前绑定的纹理对象设置环绕、过滤方式
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);//伸缩模式
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//过滤方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //生成纹理
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_w, m_h, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_buffer);//图片
    glGenerateMipmap(GL_TEXTURE_2D);//多级渐远纹理：mipmaps 1/4
    free(m_buffer);

    m_Program = GLUtils::glProgram(vertexTexture, fragmentTexture);
    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);
    glGenBuffers(1, &m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesTexture), verticesTexture, GL_STATIC_DRAW);
    glGenBuffers(1, &m_EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    GLint texture1Map = glGetUniformLocation(m_Program, "texture1Map");
    glUniform1i(texture1Map, 0);//设置采样器对应的纹理单元
}

void TextureSample::onChanged(int w, int h) {
    glViewport(0, 0, w, h);
}

void TextureSample::onDraw() {
    if (m_Program == GL_NONE) return;
    glClear(GL_STENCIL_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glUseProgram(m_Program);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_Texture);
    glBindVertexArray(m_VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void TextureSample::onDestroy() {
    GLUtils::glProgramDel(m_Program);
    m_Program = GL_NONE;
    if (mSample) {
        delete mSample;
        mSample = nullptr;
    }
}

TextureSample *TextureSample::mSample = nullptr;

TextureSample *TextureSample::instance() {
    if (mSample == nullptr) mSample = new TextureSample();
    return mSample;
}
}


