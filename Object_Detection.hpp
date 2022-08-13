#pragma once
#ifndef ObjectDetect
#define ObjectDetect
bool detect_from_video(cv::Mat& src, float confidence_threshold);
#endif