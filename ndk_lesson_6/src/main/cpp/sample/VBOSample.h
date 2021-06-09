#ifndef NDKER_VBOSAMPLE_H
#define NDKER_VBOSAMPLE_H

#include "../util/GLUtils.h"

class VBOSample {
    VBOSample() {
        mProgram = 0;
        mVBO1 = 0;
        mVBO2 = 0;
    }

public:
    void onInit();

    void onChanged(int w, int h);

    void onDraw();

    void onDestroy();

    static VBOSample *instance();

protected:
    static VBOSample *mInstance;
    GLuint mProgram;
    GLuint mVBO1;
    GLuint mVBO2;
};


#endif //NDKER_VBOSAMPLE_H
