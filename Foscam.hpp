// Skripsie_een kamera.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//***Files includes***//
//***Files includes***//

//***Includes***//
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
#include <mutex>

//Includes
//#include "Object_Detection.cpp"
//Includes
//Mat Image;    
//Mat Image_Display;
//Mat Test;
//std::mutex Save_Mutex;
//std::mutex Sleep_Mutex;
//bool which_Temp_Stack = 0;
//bool stack0_cleared = 1;
//bool stack1_cleared = 1;

class Temporary_Stacks
{
    public:
    std::vector<cv::Mat>Temp_Stack0;
    std::vector<cv::Mat>Temp_Stack1;
};
using namespace std;
using namespace cv;

void Save(VideoWriter& Output, std::shared_ptr<Temporary_Stacks>Temporary_Stacks_ptr, bool which_stack){}




void Get_New_frame(){}

void Display_Images_Real_Time(){}

void Sleeping_Thread(){}

void Short_Sleep(){}

int FOSCAM(){}
