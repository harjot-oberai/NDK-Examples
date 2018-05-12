#include <jni.h>
#include <string>

extern "C"
JNIEXPORT jstring JNICALL
Java_com_sdsmdg_harjot_ndklecturetest4_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */,
        jint a,
        jint b) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}
