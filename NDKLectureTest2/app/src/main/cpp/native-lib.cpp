#include <jni.h>
#include <string>
#include <opencv2/core/core.hpp>

using namespace std;
using namespace cv;

extern "C"
JNIEXPORT jstring JNICALL
Java_com_sdsmdg_harjot_ndklecturetest2_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}
