#ifndef NDKER_CAMERASAMPLE_H
#define NDKER_CAMERASAMPLE_H

#include "../util/GLUtils.h"
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/gtc/type_ptr.hpp"

class CameraSample {
public:
    void onImage(uint8_t *buffer1, int size1, int w1, int h1, uint8_t *buffer2, int size2,
                 int w2, int h2);

    void onInit();

    void onChanged(int w, int h);

    void onDraw();

    void onDestroy();

    static CameraSample *instance();

    void zBuffer();

    void modelMatrix3DWorld();

    void viewMatrix();

    void projectionMatrixOrthographic();

    void projectionMatrixPerspective();

    void cameraMatrix();

protected:
    GLuint m_Texture1;
    GLuint m_Texture2;
    GLuint m_Program;
    GLuint m_VAO;
    GLuint m_VBO;
    uint8_t *m_ImageBuffer1;
    int m_ImageSize1;
    int m_ImageWidth1;
    int m_ImageHeight1;
    uint8_t *m_ImageBuffer2;
    int m_ImageSize2;
    int m_ImageWidth2;
    int m_ImageHeight2;
private:
    static CameraSample *mSample;
};


#endif //NDKER_CAMERASAMPLE_H
