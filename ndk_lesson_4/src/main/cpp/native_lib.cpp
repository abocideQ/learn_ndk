#include <jni.h>
#include <string>
#include <android/log.h>

extern "C" {
JNIEXPORT jstring
JNICALL
Java_lin_abcdq_ndk4_JNITest_JNIString(JNIEnv *env, jobject obj) {
    std::string hello = "from c jni method";
    return env->NewStringUTF(hello.c_str());
}
}

