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
int height;


bool Similarity(Mat& ImageOLD, Mat& ImageNEW, int& Height, int& Width)
{
    std::vector<cv::Mat> Image_segments;
    //image is to be devided into 8 segments for better image similarity testing
    //Width of image
    int Width_per_segment = Width / 8;

    Rect ROI1(0, 0, Width_per_segment, Height);
    Rect ROI2(Width_per_segment, 0, Width_per_segment, Height);
    Rect ROI3((2 * Width_per_segment), 0, Width_per_segment, Height);
    Rect ROI4((3 * Width_per_segment), 0, Width_per_segment, Height);
    Rect ROI5(4 * Width_per_segment, 0, Width_per_segment, Height);
    Rect ROI6(5 * Width_per_segment, 0, 2 * Width_per_segment, Height);
    Rect ROI7((6 * Width_per_segment), 0, Width_per_segment, Height);
    Rect ROI8((7 * Width_per_segment), 0, Width_per_segment, Height);

    cv::Mat ROI_1O = ImageOLD(ROI1);
    cv::Mat ROI_1N = ImageNEW(ROI1);
    auto errorL2_1 = norm(ROI_1O, ROI_1N, NORM_L2);
    auto similarity1 = 1 - errorL2_1 / (height * Width_per_segment);

    cv::Mat ROI_2O = ImageOLD(ROI2);
    cv::Mat ROI_2N = ImageNEW(ROI2);
    auto errorL2_2 = norm(ROI_2O, ROI_2N, NORM_L2);
    auto similarity2 = 1 - errorL2_2 / (height * Width_per_segment);

    cv::Mat ROI_3O = ImageOLD(ROI3);
    cv::Mat ROI_3N = ImageNEW(ROI3);
    auto errorL2_3 = norm(ROI_3O, ROI_3N, NORM_L2);
    auto similarity3 = 1 - errorL2_3 / (height * Width_per_segment);

    cv::Mat ROI_4N = ImageNEW(ROI4);
    cv::Mat ROI_4O = ImageOLD(ROI4);
    auto errorL2_4 = norm(ROI_4O, ROI_4N, NORM_L2);
    auto similarity4 = 1 - errorL2_4 / (height * Width_per_segment);

    cv::Mat ROI_5N = ImageNEW(ROI5);
    cv::Mat ROI_5O = ImageOLD(ROI5);
    auto errorL2_5 = norm(ROI_5O, ROI_5N, NORM_L2);
    auto similarity5 = 1 - errorL2_5 / (height * Width_per_segment);

    cv::Mat ROI_6N = ImageNEW(ROI6);
    cv::Mat ROI_6O = ImageOLD(ROI6);
    auto errorL2_6 = norm(ROI_6O, ROI_6N, NORM_L2);
    auto similarity6 = 1 - errorL2_6 / (height * Width_per_segment);

    cv::Mat ROI_7N = ImageNEW(ROI7);
    cv::Mat ROI_7O = ImageOLD(ROI7);
    auto errorL2_7 = norm(ROI_7O, ROI_7N, NORM_L2);
    auto similarity7 = 1 - errorL2_7 / (height * Width_per_segment);

    cv::Mat ROI_8N = ImageNEW(ROI8);
    cv::Mat ROI_8O = ImageOLD(ROI8);
    auto errorL2_8 = norm(ROI_8O, ROI_8N, NORM_L2);
    auto similarity8 = 1 - errorL2_8 / (height * Width_per_segment);

    if ((similarity1 > 0.92) && (similarity2 > 0.92) && (similarity3 > 0.92) && (similarity4 > 0.92) && (similarity5 > 0.92) && (similarity6 > 0.92) && (similarity7 > 0.92) && (similarity8 > 0.92))
    {
        //cout << "The images are similar, the Old frame should be discarded" << endl;
        return 0;
    }
    else
    {
        //cout << "The images are different enough so save" << endl;
        return 1;
    }
}