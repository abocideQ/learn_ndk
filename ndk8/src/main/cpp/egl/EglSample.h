#ifndef NDKER_EGLSAMPLE_H
#define NDKER_EGLSAMPLE_H

#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <EGL/eglplatform.h>
#include <EGL/egl.h>
#include <GLES3/gl3.h>

class EglSample {
public:
    void onCreate();

    void onDestroy();
protected:
    EGLConfig m_Config;
    EGLDisplay m_Display;
    EGLSurface m_Surface;
    EGLContext m_Context;
};

#endif //NDKER_EGLSAMPLE_H
