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
#include "Object_Detection.cpp"
//Includes
Mat Image;    
Mat Image_Display;
Mat Test;
std::mutex Save_Mutex;
std::mutex Sleep_Mutex;
bool which_Temp_Stack = 0;
bool stack0_cleared = 1;
bool stack1_cleared = 1;

class Temporary_Stacks
{
    public:
    std::vector<cv::Mat>Temp_Stack0;
    std::vector<cv::Mat>Temp_Stack1;
};
std::shared_ptr<Temporary_Stacks>Temporary_Stacks_ptr = std::make_shared<Temporary_Stacks>();

using namespace std;
using namespace cv;

cv::VideoCapture Cap_Foscam("rtsp://admin:@192.168.0.185:88/videoMain");


void Save(VideoWriter& Output, std::shared_ptr<Temporary_Stacks>Temporary_Stacks_ptr, bool which_stack)
{
    std::lock_guard<mutex> lock(Save_Mutex);

     if (!which_stack)//Now the Temp_stack0 is being filled.
    {
        //stack0_cleared = 0;
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
        //stack1_cleared = 0;
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



void Get_New_frame()
{
    using namespace std::literals::chrono_literals;
    while (1)
    {
        Cap_Foscam.grab();        
        std::this_thread::sleep_for(0.05s);

    }
} 

void Display_Images_Real_Time()
{
    while (1)
    {
        if (Cap_Foscam.isOpened())
        {
            if (Cap_Foscam.retrieve(Image_Display))            
            {                
                imshow("Foscam Real Time Feed", Image_Display);
                waitKey(1);                
            }
        std::this_thread::sleep_for(0.05s);
        }
        else
        {
            cout << "Connecting...\n";
        }

    }

}

void Sleeping_Thread()
{

    std::this_thread::sleep_for(0.25s);
}
void Short_Sleep()
{
    std::lock_guard<mutex>lock(Sleep_Mutex);
    cout<<"sleeping"<<endl;
    std::this_thread::sleep_for(0.005s);
}

//void Resize_Image()
//{
//    if(Cap_Foscam.read(Image));
//    {
//    cv::resize(Image, Image, Size(), 0.5, 0.5);  
//    cout<<"Resize\n";          
//    }  
//
//}

int FOSCAM()
{
    int img_ctr = 0;
    bool Persons_was_detected;
    int Temp_Stack_Size = 10;

    Temporary_Stacks_ptr->Temp_Stack0.reserve(Temp_Stack_Size);
    Temporary_Stacks_ptr->Temp_Stack1.reserve(Temp_Stack_Size);



    int width = (Cap_Foscam.get(3));
    int height = (Cap_Foscam.get(4));

    std::thread NEWEST_FRAME(Get_New_frame);
    std::thread Display_Real_Time(Display_Images_Real_Time);
    /////////////////////////////////capture video of Foscam/////////////////////////////////
    Object_net = dnn::readNetFromCaffe("/home/shaun/Downloads/Object_detection/MobileNetSSD_deploy.prototxt",
        "/home/shaun/Downloads/Object_detection/MobileNetSSD_deploy.caffemodel");
    if (Object_net.empty())
    {
        std::cout << "init the model net error" << std::endl;
        exit(-1);
    }  

    VideoWriter Output("Output.avi", VideoWriter::fourcc('M', 'J', 'P', 'G'), 10, Size(width, height), true);
    
    while (1)
    {
        
        while (!Cap_Foscam.isOpened())
        {
            cv::VideoCapture Cap_Foscam("rtsp://admin:@192.168.0.185:88/videoMain");            
            std::cout << "Connecting...\n";

        }

        while (Cap_Foscam.isOpened())
        {
            Cap_Foscam.retrieve(Image);
            std::cout << img_ctr << endl;
            std::thread Sleep(Sleeping_Thread);
            Sleep.join();
            //cv:resize(Image,Image,Size(),0.5,0.5);
            
            if (img_ctr >= Temp_Stack_Size)
            {
                std::cout << "detect\n";
                detect = 1;
                img_ctr = 0;
            }                    

            if (!which_Temp_Stack)
            {
                while((!stack0_cleared && !stack1_cleared))//if stack0_cleared == 0 and stack1_cleared == 0 then the push_back function should wait
                {
                    std::thread Sleep0(Short_Sleep);
                    Sleep0.join();
                }
                Temporary_Stacks_ptr->Temp_Stack0.push_back(Image.clone());
                img_ctr++;
            }
            
            else if (which_Temp_Stack)
            {
                while((!stack0_cleared && !stack1_cleared))
                {
                    std::thread Sleep1(Short_Sleep);
                    Sleep1.join();
                }
                Temporary_Stacks_ptr->Temp_Stack1.push_back(Image.clone());
                img_ctr++;
            }

            if (detect == 1)
            {
                detect = 0;
                if (!Image.empty())
                {
                    HUMAN = detect_from_video(Image, confidence_threshold);
                }

                if (HUMAN)
                {
                    std::cout << "A person is detected\n";
                if(which_Temp_Stack)//Stack 1 is going to be saved
                {
                    stack1_cleared = 0;
                }
                else
                {
                    stack0_cleared = 0;//Stack 0 is going to be saved
                }
                    std::thread Saving_StackHD(Save, std::ref(Output), Temporary_Stacks_ptr, which_Temp_Stack);
                    Saving_StackHD.detach();
                    Persons_was_detected = 1;
                }
                else if ((Persons_was_detected) && (!HUMAN))
                {

                if(which_Temp_Stack)//Stack 1 is going to be saved
                {
                    stack1_cleared = 0;
                }
                else
                {
                    stack0_cleared = 0;//Stack 0 is going to be saved
                }
                    std::thread Saving_StackHND(Save,ref(Output), Temporary_Stacks_ptr, which_Temp_Stack);
                    Saving_StackHND.detach();
                    cout<<"Human is not longer detected!"<<endl;
                    Persons_was_detected = 0;
                }
                else
                {
                    Temporary_Stacks_ptr->Temp_Stack0.clear();
                    Temporary_Stacks_ptr->Temp_Stack1.clear();
                }
                
            }
        }
        return 0;
    }
}
