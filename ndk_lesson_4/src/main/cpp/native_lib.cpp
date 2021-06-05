#include <jni.h>
#include <EGL/egl.h>
#include <GLES3/gl3.h>

extern "C" {
void native_OnSurfaceCreated(JNIEnv *env, jobject obj, jint color) {
    GLfloat redF = ((color >> 16) & 0xFF) * 1.0f / 255;
    GLfloat greenF = ((color >> 8) & 0xFF) * 1.0f / 255;
    GLfloat blueF = (color & 0xFF) * 1.0f / 255;
    GLfloat alphaF = ((color >> 24) & 0xFF) * 1.0f / 255;
    glClearColor(redF, greenF, blueF, alphaF);
}

void native_OnSurfaceChanged(JNIEnv *env, jobject obj, jint width, jint height) {
    glViewport(0, 0, width, height);
}

void native_OnDrawFrame(JNIEnv *env, jobject obj) {
    glClear(GL_COLOR_BUFFER_BIT);
}

const char *JNI_Class[] = {
        "lin/abcdq/ndk4/JNITest"
};
JNINativeMethod JNI_Methods[] = {
        {"native_OnSurfaceCreated", "(I)V",  (void *) native_OnSurfaceCreated},
        {"native_OnSurfaceChanged", "(II)V", (void *) native_OnSurfaceChanged},
        {"native_OnDrawFrame",      "()V",   (void *) native_OnDrawFrame}
};
#define JNI_LENGTH(n) (sizeof(n) / sizeof(n[0]))
jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env = NULL;
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        return JNI_ERR;
    }
    jclass clazz = env->FindClass(JNI_Class[0]);
    if (env->RegisterNatives(clazz, JNI_Methods, JNI_LENGTH(JNI_Methods)) != JNI_OK) {
        return JNI_ERR;
    }
    return JNI_VERSION_1_6;
}
}

