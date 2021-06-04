#ifndef NDKER_GLPROGRAM_H
#define NDKER_GLPROGRAM_H

#include "stdio.h"
#include "stdlib.h"
#include <GLES3/gl3.h>
#include <GLES2/gl2ext.h>

class GLProgram {
public:
    static GLuint program(const char *vertex, const char *fragment)

private:
    static GLuint shader(GLuint type, const char *p)
};


#endif //NDKER_GLPROGRAM_H
