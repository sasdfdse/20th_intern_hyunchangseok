namespace hw3
{class Monster; 
    char key;
 class Player
{
    public :
    int HP, MP, x,y;
    
    void Pplayer(int x,int y);
    void Attack(Monster &m);
    void Show_status();
    void X_move(char key);
    void Y_move(char key);


};

class Monster 
{
 public :
    int HP, x,y;
     Monster();
     void Mmonster(int x, int y, int HP);
     int Be_Attacked();

};
}
