#include <iostream>
#include "opencv2/opencv.hpp"
#include "../include/hw1_package/hw1.hpp"




void OpenCV::show_window() {


    cv::imshow("Row",src);
    cv::imshow("Green",dst);
    cv::imshow("Red",red);
    cv::imshow("Blue",blue_e);

    cv::imshow("Row_blur",src_blur);
    cv::imshow("Green_blur",dst_blur); 
    cv::imshow("Red_blur",red_blur);
    cv::imshow("Blue_blur",blue_e_blur);

}

void OpenCV::Gaussianblur() {

    // 가우시안 함수를 적용한 값을 
 

    cv::GaussianBlur(src, src_blur, cv::Size(7, 7), 0);  //  GaussianBlur 함수를 사용하여 입력 이미지 즉 src에 블러를 적용한 결과 이미지 즉 , src_blur에 저장한다. 
    cv::GaussianBlur(dst, dst_blur, cv::Size(7, 7), 0);         // size(7,7)로 선언해서 이미지의 픽셀에 7x7크기로 블러를 적용한다. //마지막 0은 x축 방향의 가우시안 표준 편차라고 한다.
    cv::GaussianBlur(red, red_blur, cv::Size(7, 7), 0);
    cv::GaussianBlur(blue_e, blue_e_blur, cv::Size(7, 7), 0);

}

void OpenCV::hsvv(){


 // 녹색 
 

    cv::cvtColor(src, hsv, cv::COLOR_BGR2HSV); // 이미지 표현 형식을 이진화  // src를 RGB 색 공간에서 Hue, Saturation, Value 색 공간으로 변환 후 결과 이미지를 hsv에 저장
    lower_g = cv::Scalar (35, 50, 50);
    upper_g = cv::Scalar (85, 255, 255); // hsv 범위 
    
    cv::inRange(hsv,lower_g, upper_g, dst); // hsv의 각 픽셀이 지정된 lower g과 upper g 범위 내에 있는지 확인하여, 해당 픽셀을 255->흰색, 범위를 벗어나면 0->검은색으로 변환하여 결과 이미지 dst에 저장

    // 빨강 
   
    cv::cvtColor(src, red_s1, cv::COLOR_BGR2HSV);
    low_r1 = cv::Scalar (0, 50, 50);
    high_r1= cv::Scalar (10, 255, 255);
  
    cv::inRange(red_s1, low_r1, high_r1, red_e1);
    // 사진 상 빨간 공의 색이 다른 부분이 존재하기에 나누어서 합치는 과정을 수행
   
    cv::cvtColor(src, red_s2, cv::COLOR_BGR2HSV);
    low_s2 = cv::Scalar (160, 100, 100);
    high_s2= cv::Scalar (180, 255, 255);
    
    cv::inRange(red_s2, low_s2, high_s2, red_e2);

    red = red_e1 + red_e2;

    
    cv::cvtColor(src, blue_s, cv::COLOR_BGR2HSV);
    low_b= cv::Scalar (100, 100, 100);
    high_b= cv::Scalar (130, 255, 255);
   
    cv::inRange(blue_s, low_b, high_b, blue_e);



}



int main()
{
    OpenCV my_opencv_object;

    my_opencv_object.path = "/home/bws/simple_lifecycle_ws/src/hw1_package/hw1.png"; // 불러올 사진 파일 경로 설정
    my_opencv_object.src = cv::imread(my_opencv_object.path , cv::IMREAD_COLOR); // src 변수에 이미지를 24bit의 3채널 BGR 컬러로 로드한다
 

    my_opencv_object.hsvv();
    my_opencv_object.Gaussianblur();

    // 윈도우 창에 출력

    my_opencv_object.show_window();    
    my_opencv_object.k = cv::waitKey(0); // 이 코드가 없으면 사진이 프로그램이 실행되자 마자 꺼짐
    return 0;
}

