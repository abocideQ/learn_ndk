#include "EglSample.h"
#include "../util/Log.h"

extern "C" {
const EGLint displayAttr[] =
        {
                EGL_RENDERABLE_TYPE, EGL_OPENGL_ES3_BIT_KHR,
                EGL_SURFACE_TYPE, EGL_PBUFFER_BIT,// pixelbuffer surface
                EGL_RED_SIZE, 8,
                EGL_GREEN_SIZE, 8,
                EGL_BLUE_SIZE, 8,
                EGL_ALPHA_SIZE, 8,// if you need the alpha channel
                EGL_DEPTH_SIZE, 8,// if you need the depth buffer
                EGL_STENCIL_SIZE, 8,
                EGL_NONE
        };
const EGLint surfaceAttr[] = {
        EGL_WIDTH, 1,
        EGL_HEIGHT, 1,
        EGL_NONE
};
const EGLint contextAttr[] = {
        EGL_CONTEXT_CLIENT_VERSION, 2,
        EGL_NONE
};
void EglSample::onCreate() {
    m_Display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    EGLint eglMajor, eglMinor;
    if (!eglInitialize(m_Display, &eglMajor, &eglMinor)) {
        LOGCATE("egl display init wrong");
        return;
    }
    EGLint numConfigs;
    if (!eglChooseConfig(m_Display, displayAttr, &m_Config, sizeof(displayAttr), &numConfigs)) {
        LOGCATE("egl config init wrong");
        return;
    }
    m_Surface = eglCreatePbufferSurface(m_Display, m_Config, surfaceAttr);
    if (m_Surface == EGL_NO_SURFACE) {
        LOGCATE("egl surface init wrong");
    }
    m_Context = eglCreateContext(m_Display, m_Config, m_Context, contextAttr);
    if (m_Context == EGL_NO_CONTEXT) {
        LOGCATE("egl context init wrong");
        return;
    }
    if (!eglMakeCurrent(m_Display, m_Surface, m_Surface, m_Context)) {
        LOGCATE("egl bind wrong");
        return;
    }
}
void EglSample::onDestroy() {
    if (m_Display != EGL_NO_DISPLAY) {
        eglMakeCurrent(m_Display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
        eglDestroySurface(m_Display, m_Surface);
        eglDestroyContext(m_Display, m_Context);
        eglReleaseThread();
        eglTerminate(m_Display);
    }
    m_Display = EGL_NO_DISPLAY;
    m_Surface = EGL_NO_SURFACE;
    m_Context = EGL_NO_CONTEXT;
}
}


