#include <iostream>
#include "opencv2/opencv.hpp"

using namespace cv;

int main()
{   
    std::string path = "/home/bws/simple_lifecycle_ws/src/hw1_package/hw1.png"; // 불러올 사진 파일 경로 설정
    Mat src = imread(path , IMREAD_COLOR); // src 변수에 이미지를 24bit의 3채널 BGR 컬러로 로드한다
 

    // 녹색 
    Mat hsv; 
    cvtColor(src, hsv, COLOR_BGR2HSV); // 이미지 표현 형식을 이진화  // src를 RGB 색 공간에서 Hue, Saturation, Value 색 공간으로 변환 후 결과 이미지를 hsv에 저장
    Scalar lower_g = Scalar (35, 50, 50);
    Scalar upper_g = Scalar (85, 255, 255); // hsv 범위 
    Mat dst;
    inRange(hsv,lower_g, upper_g, dst); // hsv의 각 픽셀이 지정된 lower g과 upper g 범위 내에 있는지 확인하여, 해당 픽셀을 255->흰색, 범위를 벗어나면 0->검은색으로 변환하여 결과 이미지 dst에 저장

    // 빨강 
    Mat red_s1;
    cvtColor(src, red_s1, COLOR_BGR2HSV);
    Scalar low_r1 = Scalar (0, 50, 50);
    Scalar high_r1= Scalar (10, 255, 255);
    Mat red_e1;
    inRange(red_s1, low_r1, high_r1, red_e1);
    // 사진 상 빨간 공의 색이 다른 부분이 존재하기에 나누어서 합치는 과정을 수행
    Mat red_s2;
    cvtColor(src, red_s2, COLOR_BGR2HSV);
    Scalar low_s2 = Scalar (160, 100, 100);
    Scalar high_s2= Scalar (180, 255, 255);
    Mat red_e2;
    inRange(red_s2, low_s2, high_s2, red_e2);

    Mat red = red_e1 + red_e2;

    Mat blue_s;
    cvtColor(src, blue_s, COLOR_BGR2HSV);
    Scalar low_b= Scalar (100, 100, 100);
    Scalar high_b= Scalar (130, 255, 255);
    Mat blue_e;
    inRange(blue_s, low_b, high_b, blue_e);

    // 가우시안 함수를 적용한 값을 
    Mat src_blur;
    Mat dst_blur;
    Mat red_blur;
    Mat  blue_e_blur;

    GaussianBlur(src, src_blur, Size(7, 7), 0);  //  GaussianBlur 함수를 사용하여 입력 이미지 즉 src에 블러를 적용한 결과 이미지 즉 , src_blur에 저장한다. 
    GaussianBlur(dst, dst_blur, Size(7, 7), 0);         // size(7,7)로 선언해서 이미지의 픽셀에 7x7크기로 블러를 적용한다. //마지막 0은 x축 방향의 가우시안 표준 편차라고 한다.
    GaussianBlur(red, red_blur, Size(7, 7), 0);
    GaussianBlur(blue_e, blue_e_blur, Size(7, 7), 0);

    // 윈도우 창에 출력
    imshow("Row",src);
    imshow("Green",dst);
    imshow("Red",red);
    imshow("Blue",blue_e);

    imshow("Row_blur",src_blur);
    imshow("Green_blur",dst_blur); 
    imshow("Red_blur",red_blur);
    imshow("Blue_blur",blue_e_blur);
    int k = waitKey(0); // 이 코드가 없으면 사진이 프로그램이 실행되자 마자 꺼짐
    return 0;
}