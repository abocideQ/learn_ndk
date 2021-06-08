#include "jni.h"
#include "sample/TextureSample.h"
#include "util/Log.h"

extern "C" {
void native_OnSetData(JNIEnv *env, jobject obj, jfloatArray buffer, jint bufferSize, jint color) {
    jfloat *bf = env->GetFloatArrayElements(buffer, JNI_FALSE);
    TriangleSample::instance()->onSetData(bf, bufferSize, color);
}

void native_OnSurfaceCreated(JNIEnv *env, jobject obj) {
    TriangleSample::instance()->onInit();
}

void native_OnSurfaceChanged(JNIEnv *env, jobject obj, jint width, jint height) {
    TriangleSample::instance()->onChanged(width, height);
}

void native_OnDrawFrame(JNIEnv *env, jobject obj) {
    TriangleSample::instance()->onDraw();
}

void native_OnDestroy(JNIEnv *env, jobject obj) {
    TriangleSample::instance()->onDestroy();
}

const char *JNI_Class[] = {
        "lin/abcdq/ndk6/JNITest"
};
JNINativeMethod JNI_Methods[] = {
        {"native_OnSetData",        "([FII)V", (void *) native_OnSetData},
        {"native_OnSurfaceCreated", "()V",     (void *) native_OnSurfaceCreated},
        {"native_OnSurfaceChanged", "(II)V",   (void *) native_OnSurfaceChanged},
        {"native_OnDrawFrame",      "()V",     (void *) native_OnDrawFrame},
        {"native_OnDestroy",        "()V",     (void *) native_OnDestroy},
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

