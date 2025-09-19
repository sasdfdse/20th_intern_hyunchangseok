#include <iostream>

namespace hw2{

   
 class Cal{ 
    
 
 public: 
        void input();
        struct map
    {
    int x;
    int y;
    int num;
    int max;
    int min;
    };
        
    void create_print();
    void dist_cal();

   

  private :     // 메인에서 못씀
        int num;
        int max;
        int min;
        double max__dist=0;
        double min__dist=1000000;

        int max_dist_x=0;
        int min_dist_y=1000000;

        int max__point1=0;
        int max__point2=0 ;

        int min__point1=0;
        int min__point2=0 ;

        map *Guzo;
        double dist=0;
    
        void max_dist(double num,int point3, int point4);
        void min_dist(double num1,int point1, int point2);
    



};

}