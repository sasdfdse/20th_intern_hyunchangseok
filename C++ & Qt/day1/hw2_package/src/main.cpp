#include <iostream>
#include "../include/Head.hpp"
#include <cstdlib> 
#include <ctime>
#include <cmath> 


using namespace std;


void hw2::Cal::max_dist(double num,int point3, int point4) {

     if(num>max__dist) 
     {  max__dist = num ;
        max__point1 = point3;
        max__point2 = point4;
     }
}

void hw2::Cal::min_dist(double num1,int point1, int point2) {

     if(num1<min__dist) {
        min__dist = num1 ;
        
        min__point1 = point1;
        min__point2 = point2;
     }
}


void hw2::Cal::input() {
 
 
 cout<< "좌표의 개수를 입력해주세요.: ";
 cin>> num;
 if(num<0) {cout<<"양수를 입력하세요"; exit(1); }
 if (std::cin.fail()) {
        std::cout << "양수를 입력하세요." << std::endl; 
        exit(1);}
 cout<< "좌표의 최소 범위를 입력해주세요.: ";
 cin >> min;
 cout<< "좌표의 최대 범위를 입력해주세요.: ";
 cin >> max;
if(max<min) {cout<<"최대 범위가 최소 범위보다 작습니다."; exit(1); }
if (std::cin.fail()) {
        std::cout << "정수가 아닙니다." << std::endl; 
        exit(1);}
        
    Guzo = new hw2::Cal::map[num];

    for(int i=0; i<num; i++) {

       Guzo[i].x = rand() % (max - min + 1) + min;
        Guzo[i].y = rand() % (max - min + 1) + min;


    

 }

}

void hw2::Cal::create_print() {
    cout<<"생성된 좌표 출력"<< endl;
    cout<<"\n";

    for(int i=0; i<num; i++){
        cout << "point" << i+1<< ". X = " << Guzo[i].x << " , Y =" << Guzo[i].y << endl;

    }

}

void hw2::Cal::dist_cal() {

    for(int i=0; i<num; i++) {

        for(int k=i+1; k<num; k++){

            dist = std::sqrt(
             std::pow(Guzo[i].x - Guzo[k].x, 2) +
             std::pow(Guzo[i].y - Guzo[k].y, 2));

            max_dist(dist,i,k);
            min_dist(dist,i,k);
        } 

 }

 cout << "최소 거리: " << min__dist << endl;
 cout << "해당 좌표: P1(" << Guzo[min__point1].x << ","
 << Guzo[min__point1].y<< ") & P2(" << Guzo[min__point2].x <<
 ","<< Guzo[min__point2].y << ")" << endl;


 cout << "최대 거리:" << max__dist << endl;
 cout << "해당 좌표: P1(" << Guzo[max__point1].x << ","
 << Guzo[max__point1].y<< ") & P2(" << Guzo[max__point2].x <<
 ","<< Guzo[max__point2].y << ")" << endl;
  
    delete[] Guzo ;
}

int main() {
    
    hw2::Cal Guzo;
    Guzo.input();
    
    cout<<"\n\n";
     
    Guzo.create_print();
    Guzo.dist_cal();
 
 
    return 0;
}
