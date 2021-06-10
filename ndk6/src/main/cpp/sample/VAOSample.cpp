#include "VAOSample.h"

extern "C" {
const float triangleVertex1[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
};

const float triangleVertex2[] = {
        0.5f, 0.5f, 0.0f,
        0.5f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f
};

const char *vertexVAO = "#version 300 es                               \n"
                        "layout (location = 0) in vec4 vPosition;      \n"
                        "void main()                                   \n"
                        "{                                             \n"
                        "gl_Position = vPosition;                      \n"
                        "}                                             \n";

const char *fragmentsVAO = "#version 300 es                             \n"
                           "precision mediump float;                    \n"
                           "out vec4 fragColor;                         \n"
                           "void main(){                                \n"
                           "fragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);   \n"
                           "}                                           \n";

void VAOSample::onInit() {
    mProgram = GLUtils::glProgram(vertexVAO, fragmentsVAO);

    glGenVertexArrays(1, &mVAO1);//创建VAO
    glBindVertexArray(mVAO1);//绑定VAO
    glGenBuffers(1, &mVBO1);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertex1), triangleVertex1, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * (sizeof(float)), (void *) 0);
    glEnableVertexAttribArray(0);

    glGenVertexArrays(1, &mVAO2);//创建VAO
    glBindVertexArray(mVAO2);//绑定VAO
    glGenBuffers(1, &mVBO2);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertex2), triangleVertex2, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * (sizeof(float)), (void *) 0);
    glEnableVertexAttribArray(0);
}

void VAOSample::onChanged(int w, int h) {
    glViewport(0, 0, w, h);
}

void VAOSample::onDraw() {
    if (mProgram == GL_NONE) return;
    glClear(GL_STENCIL_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glUseProgram(mProgram);
    glBindVertexArray(mVAO1);//切换VAO
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(mVAO2);//切换VAO
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
void VAOSample::onDestroy() {}

VAOSample *VAOSample::mInstance = nullptr;

VAOSample *VAOSample::instance() {
    if (mInstance == nullptr) mInstance = new VAOSample();
    return mInstance;
}
}