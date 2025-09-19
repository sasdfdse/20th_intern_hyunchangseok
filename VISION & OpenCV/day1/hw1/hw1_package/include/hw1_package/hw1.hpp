#include <iostream>
#include "opencv2/opencv.hpp"


class OpenCV{

private:
    cv::Mat hsv; 
    cv::Mat dst;
    cv::Mat red_s1;
    cv::Mat red_e1;
    cv::Mat red_s2;
    cv::Mat red_e2;
    cv::Mat blue_e;
    cv::Mat blue_s;
    cv::Mat red;




    cv::Mat src_blur;
    cv::Mat dst_blur;
    cv::Mat red_blur;
    cv::Mat  blue_e_blur;
  


    
    


    cv::Scalar lower_g; 
    cv::Scalar upper_g;
   cv:: Scalar low_r1;
    cv::Scalar high_r1;
    cv::Scalar low_s2;
    cv::Scalar high_s2;
    cv::Scalar low_b;
    cv::Scalar high_b;




public :

void show_window();

void Gaussianblur();

void hsvv();

cv::Mat src;
std::string path;
int k;

};