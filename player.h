#include <iostream>

using namespace std;

class Player{ // objeto player con metodos get set y constructor de numero de jugador
    private:
    int tile, playerNum; 

    public:
    Player(int num){
        playerNum = num;
        tile = 1;
    }
    void setTile(int o){
        tile = o;
    }
    int getTile(){
        return tile;
    }
    int getplayerNum(){
        return playerNum;
    }
};