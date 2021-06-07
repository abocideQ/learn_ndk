#ifndef NDKER_TRIANGLE_H
#define NDKER_TRIANGLE_H

#include "../util/GLUtils.h"

class TriangleSample {
public:
    TriangleSample() {
        m_Vertex = 0;
        m_Fragment = 0;
        m_Program = 0;
        m_SurfaceWidth = 0;
        m_SurfaceHeight = 0;
    }

    void onSetData(float *bufferArray, int arraySize, int color);

    void onInit();

    void onChanged(int w, int h);

    void onDraw();

    void onDestroy();

    static TriangleSample *instance();

protected:
    GLuint m_Vertex;
    GLuint m_Fragment;
    GLuint m_Program;
    float mData[9];
    float mColor[4];
    int m_SurfaceWidth;
    int m_SurfaceHeight;

private:
    static TriangleSample *mSample;
};

#endif //NDKER_TRIANGLE_H
