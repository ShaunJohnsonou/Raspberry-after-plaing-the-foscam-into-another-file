#ifndef ObjectDetect
#define ObjectDetect
#include <thread>
#include <iostream>
#include <chrono>
#include <vector>
#include <opencv2/videoio/videoio.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/video/video.hpp>
#include <memory>
#include <filesystem>
#include <ctime>
#include "Object_Detection.hpp"
using namespace std;
using namespace cv;

//Variables
bool HUMAN;
bool detect;
const float confidence_threshold = 0.6;
const float scaleFector = 0.007843f;
const float meanVal = 127.5;
//Variables

cv::dnn::Net Object_net;

const char* class_video_Names[] = { "background",
"aeroplane", "bicycle", "bird", "boat",
"bottle", "bus", "car", "cat", "chair",
"cow", "diningtable", "dog", "horse",
"motorbike", "person", "pottedplant",
"sheep", "sofa", "train", "tvmonitor" };

bool detect_from_video(Mat& src, float confidence_threshold)
{
    size_t det_index;

    Mat blobimg = dnn::blobFromImage(src, scaleFector, Size(300, 300), meanVal);//Dit gee soms hier n error

    Object_net.setInput(blobimg, "data");

    Mat detection = Object_net.forward("detection_out");
    Mat detectionMat(detection.size[2], detection.size[3], CV_32F, detection.ptr<float>());


    for (int i = 0; i < detectionMat.rows; i++)
    {
        float detect_confidence = detectionMat.at<float>(i, 2);


        if (detect_confidence > confidence_threshold)
        {
            size_t det_index = (size_t)detectionMat.at<float>(i, 1);


            float x1 = detectionMat.at<float>(i, 3) * src.cols;
            float y1 = detectionMat.at<float>(i, 4) * src.rows;
            float x2 = detectionMat.at<float>(i, 5) * src.cols;
            float y2 = detectionMat.at<float>(i, 6) * src.rows;
            Rect rec((int)x1, (int)y1, (int)(x2 - x1), (int)(y2 - y1));

            rectangle(src, rec, Scalar(0, 0, 255), 2, 8, 0);
            putText(src, format("%s", class_video_Names[det_index]), Point(x1, y1 - 5), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(0, 0, 255), 2, 8, 0);
            putText(src, format("%0.2f", detect_confidence), Point(x1, y1 - 20), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(0, 0, 255), 2, 8, 0);
            if (det_index == 15)
            {
                return 1;
            }            
        }
        return 0;
    }
    return 0;
}
#endif