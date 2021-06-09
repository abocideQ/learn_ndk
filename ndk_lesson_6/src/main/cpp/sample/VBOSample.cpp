#include "VBOSample.h"


extern "C" {
const float triangleVertex1[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
};

const float triangleVertex2[] = {
        0.0f, 0.5f, 0.0f,
        0.0f, 0.0f, 0.0f,
        0.5f, 0.0f, 0.0f
};

const char *vertexVBO = "#version 300 es                               \n"
                     "layout (location = 0) in vec4 vPosition;      \n"
                     "void main()                                   \n"
                     "{                                             \n"
                     "gl_Position = vPosition;                      \n"
                     "}                                             \n";

const char *fragmentVBO = "#version 300 es                             \n"
                       "precision mediump float;                    \n"
                       "out vec4 fragColor;                         \n"
                       "void main(){                                \n"
                       "fragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);   \n"
                       "}                                           \n";

void VBOSample::onInit() {
    //VBO 绑定一个对应的FLOAT数组数据 供使用,如有多个VBO，每次切换不同的VBO 步骤较多 后面使用VAO
    mProgram = GLUtils::glProgram(vertexVBO, fragmentVBO);
    //复制顶点数组到缓冲中供OpenGL使用
    //GL_STATIC_DRAW ：数据不会或几乎不会改变。
    //GL_DYNAMIC_DRAW：数据会被改变很多。
    //GL_STREAM_DRAW ：数据每次绘制时都会改变。
    glGenBuffers(1, &mVBO1);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertex1), triangleVertex1, GL_STATIC_DRAW);
    // 0:location , 3: vec3 , GL_GLOAT:type, GL_FALSE :数据标准化
    // 3 * (sizeof(float)): 步长，连续的顶点属性组之间的间隔，下个组位置数据在3个float之后，我们也可以设置为0来让OpenGL决定具体步长是多少（只有当数值是紧密排列时才可用）
    // (void*)0 : 位置数据在缓冲中起始位置的偏移量(Offset)。由于位置数据在数组的开头，所以这里是0
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * (sizeof(float)), (void *) 0);
    glEnableVertexAttribArray(0);
}

void VBOSample::onChanged(int w, int h) {
    glViewport(0, 0, w, h);
}

void VBOSample::onDraw() {
    if (mProgram == GL_NONE) return;
    glClear(GL_STENCIL_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glUseProgram(mProgram);
//    glBindBuffer(GL_ARRAY_BUFFER, mVBO1);//无效代码
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void VBOSample::onDestroy() {}

VBOSample *VBOSample::mInstance = nullptr;
VBOSample *VBOSample::instance() {
    if (mInstance == nullptr) mInstance = new VBOSample();
    return mInstance;
}
}