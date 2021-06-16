#ifndef NDKER_FBOSAMPLE_H
#define NDKER_FBOSAMPLE_H

#include "../util/GLUtils.h"

class FBOSample {
public:
    void onImageUpdate(uint8_t *buffer, int w, int h);

    void onInit();

    void onChanged(int w, int h);

    void onDraw();

    void onDestroy();

    static FBOSample *instance();

protected:
    uint8_t *m_ImageBuffer;
    int m_ImageWidth;
    int m_ImageHeight;
    GLuint m_Program;
    GLuint m_ProgramFbo;
    GLuint m_Texture;
    GLuint m_TextureFbo;
    GLuint m_VAO[2];
    GLuint m_VBO[4];
    GLuint m_FBO;
    int displayWidth;
    int displayHeight;
private:
    static FBOSample *mSample;
};


#endif //NDKER_FBOSAMPLE_H
