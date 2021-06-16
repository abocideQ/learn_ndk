#include "jni.h"
#include "util/Log.h"
#include "sample/CameraSample.h"
#include "sample/FBOSample.h"

extern "C" {
int type = 1;// 1: camera 2: fbo
void native_onImageUpdate(JNIEnv *env, jobject obj, jbyteArray data1, jint size1, jint w1, jint h1,
                          jbyteArray data2,
                          jint size2, jint w2, jint h2) {
    int len1 = env->GetArrayLength(data1);
    uint8_t *buf1 = new uint8_t[len1];
    env->GetByteArrayRegion(data1, 0, len1, reinterpret_cast<jbyte *>(buf1));

    int len2 = env->GetArrayLength(data2);
    uint8_t *buf2 = new uint8_t[len2];
    env->GetByteArrayRegion(data2, 0, len2, reinterpret_cast<jbyte *>(buf2));
    if (type == 1) {
        CameraSample::instance()->onImage(buf1, size1, w1, h1, buf2, size2, w2, h2);
    } else if (type == 2) {
        FBOSample::instance()->onImageUpdate(buf1, w1, h1);
    }
    env->DeleteLocalRef(data1);
    env->DeleteLocalRef(data2);
}

void native_OnSurfaceCreated(JNIEnv *env, jobject obj) {
    if (type == 1) {
        CameraSample::instance()->onInit();
    } else if (type == 2) {
        FBOSample::instance()->onInit();
    }
}

void native_OnSurfaceChanged(JNIEnv *env, jobject obj, jint width, jint height) {
    if (type == 1) {
        CameraSample::instance()->onChanged(width, height);
    } else if (type == 2) {
        FBOSample::instance()->onChanged(width, height);
    }
}

void native_OnDrawFrame(JNIEnv *env, jobject obj) {
    if (type == 1) {
        CameraSample::instance()->onDraw();
    } else if (type == 2) {
        FBOSample::instance()->onDraw();
    }
}

void native_OnDestroy(JNIEnv *env, jobject obj) {
    if (type == 1) {
        CameraSample::instance()->onDestroy();
    } else if (type == 2) {
        FBOSample::instance()->onDestroy();
    }
}

const char *JNI_Class[] = {
        "lin/abcdq/ndk8/JNITest"
};
JNINativeMethod JNI_Methods[] = {
        {"native_onImageUpdate",    "([BIII[BIII)V", (void *) native_onImageUpdate},
        {"native_OnSurfaceCreated", "()V",           (void *) native_OnSurfaceCreated},
        {"native_OnSurfaceChanged", "(II)V",         (void *) native_OnSurfaceChanged},
        {"native_OnDrawFrame",      "()V",           (void *) native_OnDrawFrame},
        {"native_OnDestroy",        "()V",           (void *) native_OnDestroy},
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

