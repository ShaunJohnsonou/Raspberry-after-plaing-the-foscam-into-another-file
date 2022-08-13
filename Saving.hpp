#pragma one
#ifndef Saving
#define Saving
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
using namespace std;
using namespace cv;

void Saving_Function(vector<Mat>Temp_Stack);
#endif