#include <jni.h>
#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

extern "C"
jstring
Java_com_sdsmdg_harjot_ndktest_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

vector<vector<Point> > thresh_callback(Mat mat);

extern "C"
jobjectArray
Java_com_sdsmdg_harjot_ndktest_MainActivity_convert(
        JNIEnv *env,
        jobject,
        jlong matSrcAddr,
        jlong matDestAddr,
        jlong pointArray) {
    Mat &mSrc = *(Mat *) matSrcAddr;
    Mat &mDest = *(Mat *) matDestAddr;

    Mat src_gray;

    cvtColor(mSrc, src_gray, CV_BGR2GRAY);
    blur(src_gray, src_gray, Size(3, 3));

    vector<vector<Point> > contours = thresh_callback(src_gray);
    int size = 0;

    for (int i = 0; i < contours.size(); i++) {
        size += contours[i].size();
    }

    size += contours.size();

    jclass javaClass = (env)->FindClass("com/sdsmdg/harjot/ndktest/Point");
    jobjectArray objArray = (env)->NewObjectArray(size, javaClass, NULL);
    jmethodID methodID = (env)->GetMethodID(javaClass, "<init>", "(II)V");
    jobject obj;

    int number = 0;
    for (int i = 0; i < contours.size(); i++) {
        vector<Point> points = contours[i];
        for (int j = 0; j < points.size(); j++) {
            obj = (env)->NewObject(javaClass, methodID, points[j].x, points[j].y);
            (env)->SetObjectArrayElement(objArray, number, obj);
            (env)->DeleteLocalRef(obj);
            number++;
        }
        obj = (env)->NewObject(javaClass, methodID, -1, -1);
        (env)->SetObjectArrayElement(objArray, number, obj);
        (env)->DeleteLocalRef(obj);
        number++;
    }

    return objArray;

}

int thresh = 100;
int max_thresh = 255;
RNG rng(12345);

vector<vector<Point> > thresh_callback(Mat src_gray) {
    Mat canny_output;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

    /// Detect edges using canny
    Canny(src_gray, canny_output, thresh, thresh * 2, 3);
    /// Find contours
    findContours(canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE,
                 Point(0, 0));

    /// Draw contours
//    Mat drawing = Mat::zeros(canny_output.size(), CV_8UC3);
//    for (int i = 0; i < contours.size(); i++) {
//        Scalar color = Scalar(255, 255, 255);
//        drawContours(drawing, contours, i, color, 3, 8, hierarchy, 0, Point());
//    }

    return contours;

}


