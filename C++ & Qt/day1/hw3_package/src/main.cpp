#include <iostream>
#include "../include/HEAD.hpp"

using namespace hw3;
using namespace std;

Player p;
Monster m;

void Player :: X_move(char key) 
{
    if(key=='L') {p.x -=1; cout << "X 축으로 -1 이동"<<endl;}
    else if(key=='R'){ p.x +=1; cout << "X 축으로 +1 이동"<<endl;}


}

void Player::Y_move(char key) {

    if(key=='D') {p.y -=1;  cout << "Y 축으로 -1 이동"<<endl;}
    else if(key=='U'){ p.y +=1;  cout << "Y 축으로 +1 이동"<<endl;}

}

void Player :: Show_status() {

    cout << "HP: "<< p.HP<< endl;
    cout << "MP: "<< p.MP<< endl;
    cout << "Position: "<< p.x<< "," << p.y<<endl;
}

void Player :: Attack(Monster &m) {

    
    
    m.HP-=10;


}

void Monster ::Mmonster(int x, int y, int hp) {

    m.x = x;
    m.y = y;
    m.HP = 50;
}

void Player :: Pplayer(int x, int y) {
p.x =x;
p.y = y;
p.HP = 50;
p.MP = 10;

}
int main () {

 p.Pplayer(0,0);
 m.Mmonster(5,4,50);
    while (1)
 {  
    cout << "Type Command (A/U/D/R/L/S)";
    cin >> key;
    if(key == 'M') exit(1);
    if(key!='L'&&key!='R'&&key!='D'&&key!='U'&&key!='S'&&key!='A') {cout << "올바른 키를 입력하세요."<<endl; continue;}
    p.X_move(key);
    p.Y_move(key);
    
    if(key=='S') p.Show_status();
    if(key=='A'){
        if(p.MP<1) {cout << "MP 부족 ! "<<endl; exit(1);}
        p.MP-=1;
        if(p.x==5 && p.y==4) {
        
            cout << "공격 성공!"<<endl;
            p.Attack(m);
            cout << "남은 체력: "<<m.HP <<endl;
        } 
        else {cout << "공격 실패!"<<endl;}
 
    }

    if(m.HP==0) {

        cout << "Monster die!"<<endl;
        exit(1);

    }

    }

    return 0;
}
