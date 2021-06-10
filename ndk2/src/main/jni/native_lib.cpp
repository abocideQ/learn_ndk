#include <jni.h>
#include <string>
#include <android/log.h>

extern "C" {
//JavaVM 是虚拟机在 JNI 层的代表，一个进程只有一个的全局变量，所有的线程共用一个 JavaVM。
//JNIEnv 表示 Java 调用 native 语言的环境，是一个封装了几乎全部 JNI 方法的指针。
#if defined(__cplusplus)//C++ 形式
typedef _JNIEnv JNIEnv;
typedef _JavaVM JavaVM;
#else                   //C 形式
typedef const struct JNINativeInterface* JNIEnv;
typedef const struct JNIInvokeInterface* JavaVM;
#endif
//静态注册jni
JNIEXPORT jstring
JNICALL
Java_lin_abcdq_ndk2_JNITest_JNIString(JNIEnv *env, jobject obj) {
    std::string hello = "from c jni method";
    return env->NewStringUTF(hello.c_str());
}
//动态注册jni  -- > ()Ljava/lang/String 为JVM的String
jstring JNIString(JNIEnv *env, jobject obj) {
    std::string hello = "from c jni method";
    return env->NewStringUTF(hello.c_str());
}
jint RegisterNatives(JNIEnv *env) {
    jclass clazz = env->FindClass("lin/abcdq/ndk2/JNITest");
    if (clazz == NULL) return JNI_ERR;
    JNINativeMethod methods_JNITest[] = {
            {"JNIString", "()Ljava/lang/String;", (void *) JNIString}
    };
    return env->RegisterNatives(clazz, methods_JNITest,
                                sizeof(methods_JNITest) / sizeof(methods_JNITest[0]));
}
jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env = NULL;
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        return JNI_ERR;
    }
    jint result = RegisterNatives(env);
    return JNI_VERSION_1_6;
}
}

