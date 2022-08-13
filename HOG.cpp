
/*
float Histogram_sim(Mat& IMAGE_OLD, Mat& IMAGE_NEW)
{
    //die exception is omdat die IMAGE_OLD_GREY n vector is en nie n mat nie....
    //==>so die Image_OLF_GRAY moet nie n vector wees nie...
    Mat IMAGE_OLD_GREY;
    Mat IMAGE_NEW_GREY;
    cvtColor(IMAGE_OLD, IMAGE_OLD_GREY, 6, 0);
    cvtColor(IMAGE_NEW, IMAGE_NEW_GREY, 6, 0);
    int HistogramSize = 256;
    float range[] = { 0, 255 };
    const float* HistogramRange = { range };
    int Nr_bins = HistogramSize;
    bool uniform = true, accumulate = false;
    Mat Histogram_OLD_GRAY, Histogram_NEW_GRAY;
    calcHist(&IMAGE_OLD_GREY, 1, 0, Mat(), Histogram_OLD_GRAY, 1, &HistogramSize, &HistogramRange, uniform, accumulate);
    calcHist(&IMAGE_NEW_GREY, 1, 0, Mat(), Histogram_NEW_GRAY, 1, &HistogramSize, &HistogramRange, uniform, accumulate);
    int histogram_width = 512;
    int Histogram_Height = 400;
    int Bin_Width = cvRound((double)histogram_width / HistogramSize);
    Mat HistImage_OLD(Histogram_Height, histogram_width, CV_8UC3, Scalar(0, 0, 0));
    normalize(Histogram_OLD_GRAY, Histogram_OLD_GRAY, 0, HistImage_OLD.rows, NORM_MINMAX, -1, Mat());
    normalize(Histogram_NEW_GRAY, Histogram_NEW_GRAY, 0, HistImage_OLD.rows, NORM_MINMAX, -1, Mat());
    double  similarity_of_Histograms = compareHist(Histogram_OLD_GRAY, Histogram_NEW_GRAY, 0);
    imshow("NAME", IMAGE_OLD_GREY);
    imshow("NAME2", IMAGE_NEW_GREY);
    waitKey(1);
    cout << "The correlation is: " << similarity_of_Histograms << endl;
    //Test the collelation//
    if (similarity_of_Histograms >= 0.999)//the old image should be saved
    {
        cout << "The images are similar, the Old frame should be discarded" << endl;
    }
    else
    {
        cout << "The images are different enough so save" << endl;
    }
    return similarity_of_Histograms;
}
//Test the correlation//
*/
