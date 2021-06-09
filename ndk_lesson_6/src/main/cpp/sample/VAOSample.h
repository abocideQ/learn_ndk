#ifndef NDKER_VAOSAMPLE_H
#define NDKER_VAOSAMPLE_H

#include "../util/GLUtils.h"

class VAOSample {
    VAOSample() {
        mProgram = 0;
        mVAO1 = 0;
        mVBO1 = 0;
        mVAO2 = 0;
        mVBO2 = 0;
    }

public:
    void onInit();

    void onChanged(int w, int h);

    void onDraw();

    void onDestroy();

    static VAOSample *instance();

protected:
    static VAOSample *mInstance;
    GLuint mProgram;
    GLuint mVAO1;
    GLuint mVBO1;
    GLuint mVAO2;
    GLuint mVBO2;
};


#endif //NDKER_VAOSAMPLE_H
