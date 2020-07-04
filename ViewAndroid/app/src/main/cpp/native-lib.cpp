#include <jni.h>
#include <string>

#include <opencv2/opencv.hpp>
#include "ImageProcessor.h"

#define MODEL_FILENAME "/sdcard/models/mobilenetv3_ssdlite_voc"
#define LABEL_NAME    "/sdcard/models/label_PASCAL_VOC2012.txt"

extern "C" JNIEXPORT jint JNICALL
Java_com_iwatake_viewandroid_MainActivity_ImageProcessorInitialize(
        JNIEnv* env,
        jobject /* this */) {

    int ret = 0;
    INPUT_PARAM inputParam;
    snprintf(inputParam.labelFilename, sizeof(inputParam.labelFilename), LABEL_NAME);
    ret = ImageProcessor_initialize(MODEL_FILENAME, &inputParam);
    return ret;
}

extern "C" JNIEXPORT jint JNICALL
Java_com_iwatake_viewandroid_MainActivity_ImageProcessorProcess(
        JNIEnv* env,
        jobject, /* this */
        jlong   objMat) {

    int ret = 0;
    cv::Mat* mat = (cv::Mat*) objMat;
    OUTPUT_PARAM outputParam;
    ret = ImageProcessor_process(mat, &outputParam);
    return ret;
}

extern "C" JNIEXPORT jint JNICALL
Java_com_iwatake_viewandroid_MainActivity_ImageProcessorFinalize(
        JNIEnv* env,
        jobject /* this */) {

    int ret = 0;
    ret = ImageProcessor_finalize();
    return ret;
}
