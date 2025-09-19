#include <iostream> // 
#include "../include_1/hw_1/head.hpp"

void hw1::cal::max(int num) {

     if(num>max_num) max_num = num ;
}

void hw1::cal::min(int num1) {

     if(num1<min_num) min_num = num1 ;
}


void hw1::cal::request() {

    std::cout<<"몇 개의 원소를 할당하겠습니까? : " ;
    std::cin >> try_;

    int*num = new int[try_];
    if(!num){
        std::cout<< "메모리를 사용할 수 없습니다.";
        return;
    }

    for(int i=0; i<try_; i++){

        std::cout<<"정수형 데이터 입력:" ;
        std::cin >> num[i];

        if (std::cin.fail()) {
        std::cout << "정수가 아닙니다." << std::endl; 
        return;}
        sum += num[i];
        min(num[i]);
        max(num[i]);
    }

    avg = sum / try_;

    std::cout<<"최댓값: "<<max_num << std::endl;
    std::cout<<"최솟값: "<<min_num << std::endl;
    std::cout<<"전체합: "<<sum << std::endl;
    std::cout<<"평균: "<<avg << std::endl;

    delete[] num;
}

int main(int argc, char ** argv){
    
    hw1::cal Cal;
    Cal.request();

    
}      