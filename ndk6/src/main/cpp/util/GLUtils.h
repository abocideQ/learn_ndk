#ifndef NDKER_GLUTILS_H
#define NDKER_GLUTILS_H

#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include <stdlib.h>
#include <cstring>

class GLUtils {
public:
    static GLuint glProgram(const char *vertex, const char *fragment);

    static void glProgramDel(GLuint program);

private:
    static GLuint glShader(GLenum type, const char *p);
};


#endif //NDKER_GLUTILS_H
