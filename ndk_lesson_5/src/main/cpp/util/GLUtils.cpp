#include "GLUtils.h"
#include "../util/Log.h"

extern "C" {
GLuint GLUtils::glProgram(const char *vertex, const char *fragment) {
    GLuint program = 0;
    GLuint vertexShader = glShader(GL_VERTEX_SHADER, vertex);
    if (!vertexShader) return program;
    GLuint fragmentShader = glShader(GL_FRAGMENT_SHADER, fragment);
    if (!fragmentShader) return program;
    program = glCreateProgram();
    LOGCATE("GL glProgram %d", program);
    if (program) {
        glAttachShader(program, vertexShader);
        glAttachShader(program, fragmentShader);
        glLinkProgram(program);
        GLint linkStatus = GL_FALSE;
        glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
        glDetachShader(program, vertexShader);
        glDeleteShader(vertexShader);
        vertexShader = 0;
        glDetachShader(program, fragmentShader);
        glDeleteShader(fragmentShader);
        fragmentShader = 0;
        LOGCATE("GL linkStatus1 %d", program);
        if (linkStatus != GL_TRUE) {
            LOGCATE("GL linkStatus2 %d", program);
            GLint infoLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLength);
            if (infoLength) {
                char *infoBuffer = (char *) malloc((size_t) infoLength);
                if (infoBuffer) {
                    glGetProgramInfoLog(program, infoLength, NULL, infoBuffer);
                    free(infoBuffer);
                }
                glDeleteProgram(program);
                program = 0;
            }
        }
    }
    LOGCATE("GL Create %d", program);
    return program;
}

void GLUtils::glUse(GLuint program) {
    if (program == 0) return;
    glUse(program);
}

void GLUtils::glClear(GLuint program) {
    if (program == 0) return;
    LOGCATE("GL Clear %d", program);
    glClear(GL_STENCIL_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0, 1.0, 1.0, 1.0);
}

void GLUtils::glProgramDel(GLuint program) {
    glUseProgram(0);
    glDeleteProgram(program);
}

GLuint GLUtils::glShader(int type, const char *p) {
    GLuint shader = 0;
    shader = glCreateShader(type);
    if (shader) {
        glShaderSource(shader, 1, &p, NULL);
        glCompileShader(shader);
        GLint compileStatus = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);
        if (!compileStatus) {
            GLint infoLength = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLength);
            if (infoLength) {
                char *infoBuffer = (char *) malloc((size_t) infoLength);
                if (infoBuffer) {
                    glGetShaderInfoLog(shader, infoLength, NULL, infoBuffer);
                    //ERROR:Could not compile shader
                    free(infoBuffer);
                }
                glDeleteShader(shader);
                shader = 0;
            }
        }
    }
    return shader;
}
}



