#include <jni.h>
#include <string>
#include "math_test.h"
#include <sstream>

template <typename T>
std::string NumberToString ( T Number )
{
    std::ostringstream ss;
    ss << Number;
    return ss.str();
}

std::string addNumbers(int a, int b){
    return NumberToString(add(a,b));
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_sdsmdg_harjot_ndklecturetest1_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject, jint a, jint b) {
    std::string hello = "SUM : " + (addNumbers(a,b));
    return env->NewStringUTF(hello.c_str());
}

