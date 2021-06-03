#include "LogUtil.h"
#include <stdlib.h>

class GLPrograms {
public:
    GLuint program(const char *vertical, const char *fragment);

private:
    GLuint shader(GLuint type, const char *source);
};
