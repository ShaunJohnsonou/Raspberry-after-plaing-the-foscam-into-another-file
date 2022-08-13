/*
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
#include "Saving.hpp"
using namespace std;
using namespace cv;
std::mutex Save_Mutex;

bool Save(VideoWriter& Output, std::shared_ptr<Temporary_Stacks>Temporary_Stacks_ptr, bool which_stack)
{
    std::lock_guard<mutex> lock(Save_Mutex);

     if (!which_stack)//Now the Temp_stack0 is being filled.
    {
        which_Temp_Stack = 1;
        for (int y = 0; y <= (Temporary_Stacks_ptr->Temp_Stack0.size() - 1); y++)
        {
            cout << "HOPES0\n";
            Output.write(Temporary_Stacks_ptr->Temp_Stack0[y]);
        }
    Temporary_Stacks_ptr->Temp_Stack0.clear();
    stack0_cleared = 1;
    }

    if (which_stack)//Now the Temp_stack1 is being filled.
    {
        which_Temp_Stack = 0;
        for (int y = 0; y <= (Temporary_Stacks_ptr->Temp_Stack1.size() - 1); y++)
        {
            cout << "HOPES1\n";
            Output.write(Temporary_Stacks_ptr->Temp_Stack1[y]);
        }
    Temporary_Stacks_ptr->Temp_Stack1.clear();
    stack1_cleared = 1;
    }       
}
*/