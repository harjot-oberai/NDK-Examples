#include <jni.h>
#include <string>
#include <sstream>

JNIEXPORT jstring JNICALL
Java_com_sdsmdg_harjot_ndklibrarytest_ndklibrary_TestClass_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    return env->NewStringUTF("abc");
}