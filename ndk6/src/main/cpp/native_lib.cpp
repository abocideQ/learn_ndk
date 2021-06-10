#include "jni.h"
#include "sample/VBOSample.h"
#include "sample/VAOSample.h"
#include "sample/TextureSample.h"
#include "util/Log.h"

extern "C" {
void
native_onImageUpdate(JNIEnv *env, jobject obj, jbyteArray da, jint s, jint w, jint h) {
    int len = env->GetArrayLength(da);
    uint8_t *buf = new uint8_t[len];
    env->GetByteArrayRegion(da, 0, len, reinterpret_cast<jbyte *>(buf));
    TextureSample::instance()->onImage(buf, s, w, h);
    env->DeleteLocalRef(da);
}

void native_OnSurfaceCreated(JNIEnv *env, jobject obj) {
//    VBOSample::instance()->onInit();
//    VAOSample::instance()->onInit();
    TextureSample::instance()->onInit();
}

void native_OnSurfaceChanged(JNIEnv *env, jobject obj, jint width, jint height) {
//    VBOSample::instance()->onChanged(width, height);
//    VAOSample::instance()->onChanged(width, height);
    TextureSample::instance()->onChanged(width, height);
}

void native_OnDrawFrame(JNIEnv *env, jobject obj) {
//    VBOSample::instance()->onDraw();
//    VAOSample::instance()->onDraw();
    TextureSample::instance()->onDraw();
}

void native_OnDestroy(JNIEnv *env, jobject obj) {
//    VBOSample::instance()->onDestroy();
//    VAOSample::instance()->onDestroy();
    TextureSample::instance()->onDraw();
}

const char *JNI_Class[] = {
        "lin/abcdq/ndk6/JNITest"
};
JNINativeMethod JNI_Methods[] = {
        {"native_onImageUpdate",    "([BIII)V", (void *) native_onImageUpdate},
        {"native_OnSurfaceCreated", "()V",      (void *) native_OnSurfaceCreated},
        {"native_OnSurfaceChanged", "(II)V",    (void *) native_OnSurfaceChanged},
        {"native_OnDrawFrame",      "()V",      (void *) native_OnDrawFrame},
        {"native_OnDestroy",        "()V",      (void *) native_OnDestroy},
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

