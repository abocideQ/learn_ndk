#include "FBOSample.h"
#include "../util/Log.h"

extern "C" {
GLfloat fbo_Vertex[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        -1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
};
//纹理原点位于右上角
GLfloat fbo_TexCoors[] = {
        0.0f, 1.0f,
        1.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,
};
//fbo纹理,原点位于左下角
GLfloat fbo_FboTexCoors[] = {
        0.0f, 0.0f,
        1.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
};
unsigned int fbo_Indices[] = {0, 1, 2, 1, 3, 2};
const char *fbo_vertex_shader =
        "#version 300 es                            \n"
        "layout(location = 0) in vec4 v_position;   \n"
        "layout(location = 1) in vec2 v_in_texCoord;\n"
        "out vec2 v_out_texCoord;                   \n"
        "void main()                                \n"
        "{                                          \n"
        "   gl_Position = v_position;               \n"
        "   v_out_texCoord = v_in_texCoord;         \n"
        "}                                          \n";
const char *fbo_fragment_shader =
        "#version 300 es                            \n"
        "precision mediump float;                   \n"
        "in vec2 v_out_texCoord;                    \n"
        "layout(location = 0) out vec4 outColor;    \n"
        "uniform sampler2D s_TextureMap;            \n"
        "void main()                                \n"
        "{                                          \n"
        "    outColor = texture(s_TextureMap, v_out_texCoord);\n"
        "}                                          \n";
const char *fbo_fbo_shader =    // 灰度图
        "#version 300 es                                \n"
        "precision mediump float;                       \n"
        "in vec2 v_out_texCoord;                        \n"
        "layout(location = 0) out vec4 outColor;        \n"
        "uniform sampler2D s_TextureMap;                \n"
        "void main()                                    \n"
        "{                                              \n"
        "    vec4 tempColor = texture(s_TextureMap, v_out_texCoord);\n"
        "    float luminance = tempColor.r * 0.299 + tempColor.g * 0.587 + tempColor.b * 0.114;\n"
        "    outColor = vec4(vec3(luminance), tempColor.a);\n"
        "}                                              \n";

void FBOSample::onImageUpdate(uint8_t *buffer, int w, int h) {
    m_ImageBuffer = buffer;
    m_ImageWidth = w;
    m_ImageHeight = h;
}

void FBOSample::onInit() {
    m_Program = GLUtils::glProgram(fbo_vertex_shader, fbo_fragment_shader);
    m_ProgramFbo = GLUtils::glProgram(fbo_vertex_shader, fbo_fbo_shader);

    glGenBuffers(4, m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(fbo_Vertex), fbo_Vertex, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(fbo_TexCoors), fbo_TexCoors, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(fbo_FboTexCoors), fbo_FboTexCoors, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_VBO[3]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(fbo_Indices), fbo_Indices, GL_STATIC_DRAW);

    glGenVertexArrays(2, m_VAO);
    //离屏vao
    glBindVertexArray(m_VAO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO[0]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (void *) 0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO[2]);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GL_FLOAT), (void *) 0);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_VBO[3]);
    //普通vao
    glBindVertexArray(m_VAO[1]);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO[0]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (void *) 0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO[1]);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GL_FLOAT), (void *) 0);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_VBO[3]);

    //离屏纹理
    glGenTextures(1, &m_TextureFbo);
    glBindTexture(GL_TEXTURE_2D, m_TextureFbo);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //FBO
    glGenFramebuffers(1, &m_FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
    glBindTexture(GL_TEXTURE_2D, m_TextureFbo);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_TextureFbo, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_ImageWidth, m_ImageHeight, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, nullptr);
    glBindTexture(GL_TEXTURE_2D, GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, GL_NONE);
    //普通纹理
    glGenTextures(1, &m_Texture);
    glBindTexture(GL_TEXTURE_2D, m_Texture);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_ImageWidth, m_ImageHeight, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, m_ImageBuffer);
    glGenerateMipmap(GL_TEXTURE_2D);
}

void FBOSample::onChanged(int w, int h) {
    glViewport(0, 0, w, h);
    displayWidth = w;
    displayHeight = h;
}

void FBOSample::onDraw() {
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);//!!!!!!
    //离屏渲染
    glViewport(0, 0, m_ImageWidth, m_ImageHeight);//!!!!!!!
    glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);//绑定FBO
    glUseProgram(m_ProgramFbo);
    glBindVertexArray(m_VAO[0]);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_Texture);
    GLint mTexMapFbo = glGetUniformLocation(m_ProgramFbo, "s_TextureMap");
    glUniform1i(mTexMapFbo, 0);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void *) 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);//解绑FBO
    //普通渲染
    glClear(GL_STENCIL_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glViewport(0, 0, displayWidth, displayHeight);//!!!!!!!
    glUseProgram(m_Program);
    glBindVertexArray(m_VAO[1]);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_TextureFbo);
    GLint mTexMap = glGetUniformLocation(m_Program, "s_TextureMap");
    glUniform1i(mTexMap, 0);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void *) 0);
}

void FBOSample::onDestroy() {

}
FBOSample *FBOSample::mSample = nullptr;
FBOSample *FBOSample::instance() {
    if (mSample == nullptr) mSample = new FBOSample();
    return mSample;
}
}



