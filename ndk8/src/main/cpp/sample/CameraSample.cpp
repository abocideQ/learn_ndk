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

glm::vec3 cubePositions[] = {
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(2.0f, 5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f, 3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f, 2.0f, -2.5f),
        glm::vec3(1.5f, 0.2f, -1.5f),
        glm::vec3(-1.3f, 1.0f, -1.5f)
};

const char *vertexTexture = "#version 300 es                            \n"
                            "layout(location = 0) in vec4 vPosition;    \n"
                            "layout(location = 1) in vec2 vTexCoord;    \n"
                            "out vec2 fTexCoord;                        \n"
                            "uniform mat4 model;//模型：世界空间          \n"
                            "uniform mat4 view; //视图：观察空间          \n"
                            "uniform mat4 projection;//射影：裁剪空间     \n"
                            "void main(){                               \n"
                            "gl_Position = projection * view * model * vPosition;\n"
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

    zBuffer();
    modelMatrix3DWorld();
    viewMatrix();
    projectionMatrixPerspective();
    cameraMatrix();
}

void CameraSample::onDestroy() {

}

CameraSample *CameraSample::mSample = nullptr;
CameraSample *CameraSample::instance() {
    if (mSample == nullptr) mSample = new CameraSample();
    return mSample;
}
}

//深度测试
void CameraSample::zBuffer() {
    glEnable(GL_DEPTH_TEST);
}

float modelRotation = 0.0f;

//模型矩阵：世界空间的旋转缩放移动
void CameraSample::modelMatrix3DWorld() {
    modelRotation = modelRotation + (rand() / double(RAND_MAX));
    int i = 0;
    for (; i < 10; i++) {
        glm::mat4 model = glm::mat4(1.0);
        model = glm::translate(model, cubePositions[i]);
        model = glm::rotate(model, glm::radians(modelRotation), glm::vec3(1.0f, 0.3f, 0.5f));
        model = glm::scale(model, glm::vec3(0.9, 0.9, 0.9));
        unsigned int modelMat4 = glGetUniformLocation(m_Program, "model");
        glUniformMatrix4fv(modelMat4, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}

float viewRotation = 0.0f;

//视图矩阵：观察空间
void CameraSample::viewMatrix() {
    viewRotation = viewRotation + 0.5f;
    glm::mat4 view = glm::mat4(1.0f);
    //vev3 参数对应 X,Y,Z
    view = glm::translate(view, glm::vec3(0.0f, 1.0f, -6.0f));
    view = glm::rotate(view, glm::radians(viewRotation), glm::vec3(0.0f, 1.0f, 0.0f));
    unsigned int viewMat4 = glGetUniformLocation(m_Program, "view");
    glUniformMatrix4fv(viewMat4, 1, GL_FALSE, glm::value_ptr(view));
}

//正射投影矩阵：裁剪空间
void CameraSample::projectionMatrixOrthographic() {
    //0.0f：左边界左边 1080:右边界坐标，1080：宽1080高1080的显示区域，1.0f,10000.0f :近点到远点距离
    glm::mat4 proj = glm::mat4(1.0);
    proj = glm::ortho(0.0f, 1080.0f, 0.0f, 1080.0f, 1.0f, 1000.0f);
    unsigned int projectionMat4 = glGetUniformLocation(m_Program, "projection");
    glUniformMatrix4fv(projectionMat4, 1, GL_FALSE, glm::value_ptr(proj));
}

//透视投影矩阵：裁剪空间
void CameraSample::projectionMatrixPerspective() {
    //45：视野范围，1080：宽1080高1080的显示区域，1.0f,10000.0f :近点到远点距离
    glm::mat4 proj = glm::mat4(1.0);
    proj = glm::perspective(glm::radians(45.0f), 1080.0f / 1080.0f, 1.0f, 1000.0f);
    unsigned int projectionMat4 = glGetUniformLocation(m_Program, "projection");
    glUniformMatrix4fv(projectionMat4, 1, GL_FALSE, glm::value_ptr(proj));
}

//摄像机:视图矩阵实现
void CameraSample::cameraMatrix() {
    glm::mat4 view = glm::mat4(1.0f);
    //参数：摄像机位置，目标位置，世界空间中的上向量的向量(一般为vec3(0.0f, 1.0f, 0.0f)不变)
    view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f),
                       glm::vec3(0.0f, 1.0f, 0.0f));
    unsigned int viewMat4 = glGetUniformLocation(m_Program, "view");
    glUniformMatrix4fv(viewMat4, 1, GL_FALSE, glm::value_ptr(view));
}

