#include <jni.h>
#include <string>
#include <math_test.h>
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
Java_com_sdsmdg_harjot_ndklecturetest3_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Sum : " + addNumbers(3,4);
    return env->NewStringUTF(hello.c_str());
}
