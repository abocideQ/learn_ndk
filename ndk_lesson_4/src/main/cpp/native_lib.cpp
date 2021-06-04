#include <jni.h>
#include <EGL/egl.h>
#include <GLES3/gl3.h>

extern "C" {
//render
void JNISurfaceCreate(JNIEnv *env, jobject obj, jint color) {
    GLfloat redF = ((color >> 16) & 0xFF) * 1.0f / 255;
    GLfloat greenF = ((color >> 8) & 0xFF) * 1.0f / 255;
    GLfloat blueF = (color & 0xFF) * 1.0f / 255;
    GLfloat alphaF = ((color >> 24) & 0xFF) * 1.0f / 255;
    glClearColor(redF, greenF, blueF, alphaF);
}
void JNISurfaceChange(JNIEnv *env, jobject obj, jint width, jint height) {
    glViewport(0, 0, width, height);
}
void JNIOnDrawFrame(JNIEnv *env, jobject obj) {
    //把颜色缓冲区设置为我们预设的颜色
    glClear(GL_COLOR_BUFFER_BIT);
}
jint JNI_RegisterNatives(JNIEnv *env) {
    jclass clazz = env->FindClass("lin/abcdq/ndk4/JNITest");
    JNINativeMethod methods[] = {
            {"JNISurfaceCreate", "(I)V",  (void *) JNISurfaceCreate},
            {"JNISurfaceChange", "(II)V", (void *) JNISurfaceChange},
            {"JNIOnDrawFrame",   "()V",   (void *) JNIOnDrawFrame}
    };
    return env->RegisterNatives(clazz, methods,
                                sizeof(methods) / sizeof(methods[0]));
}
jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env = NULL;
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        return JNI_ERR;
    }
    JNI_RegisterNatives(env);
    return JNI_VERSION_1_6;
}
}

