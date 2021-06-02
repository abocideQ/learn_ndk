#include <jni.h>
#include <string>
#include <android/log.h>
//JNIEnv 表示 Java 调用 native 语言的环境，是一个封装了几乎全部 JNI 方法的指针。
//jxxxxx jni 中对象的用法 如：jint jstring jobject
extern "C" {
JNIEXPORT jstring
JNICALL
Java_lin_abcdq_ndk1_JNITest_JNIString(JNIEnv *env, jobject obj) {
    std::string hello = "from c jni method";
    return env->NewStringUTF(hello.c_str());
}
}

