#include "tile.h"
#include <iostream>
#include <vector>
#include <cstdlib> 

using namespace std;

class board{
    private:
    int tilesNumber;
    vector<tile*> gameBoard;

    public:

    board(int tilesNum, int snakeTiles, int ladderTiles): tilesNumber(tilesNum){

        srand(time(0)); //semilla de funcion aleatoria de libreria
        
        int snaketiles[snakeTiles];
        int laddertiles[ladderTiles];
        int num;
        bool pass;

        for (int i = 0; i < snakeTiles; i++)
        {
            num = rand() % tilesNum;
            pass = true;

            if (num == 1)
            {
                i -= 1; 
                continue;
            }

        for (size_t o = 0; o < snakeTiles; o++) {
            if (num == snaketiles[o]) {
                pass = false; // checa si el valor se repite en snakeTiles
                break;
            }
        }
        if (pass == false) {
            i -= 1; // checa si no está aprobado por el check
            continue; // reinicia el mismo ciclo
        }
        snaketiles[i] = num;
        }

        for (int i = 0; i < ladderTiles; i++)
        {
            num = rand() % tilesNum;
            pass = true;

            if (num == 1)
            {
                i -= 1; 
                continue;
            }
            

            for (size_t o = 0; o < snakeTiles; o++) {
                if (num == snaketiles[o]) {
                    pass = false; // checa si el valor se repite en snakeTiles
                    break;
                }
            }

            if (pass == true) {
                for (size_t o = 0; o < ladderTiles; o++) {
                    if (num == laddertiles[o]) {
                        pass = false; // checa si el valor se repite en ladderTiles
                        break;
                    }
                }
            }

            if (pass == false) {
                i -= 1; // checa si no está aprobado por los dos checks
                continue; // reinicia el mismo ciclo
            }
            laddertiles[i] = num;
        }
        for (size_t i = 2; i < tilesNum; i++)
        {
            pass = true;
            for (size_t o = 0; o < snakeTiles; o++)
            {
                if(snaketiles[o] == i){
                    gameBoard.push_back(new serpentTile(i));
                    pass = false;
                    break;
                }
            }
            if(pass == true){
            for (size_t o = 0; o < ladderTiles; o++)
            {
                if(laddertiles[o] == i){
                    gameBoard.push_back(new ladderTile(i));
                    pass = false;
                    break;
                }
            }    
            }
            if(pass == true){
                gameBoard.push_back(new normalTile(i));
            }
        }
    }

    ~board(){
        for (size_t i = 0; i < gameBoard.size(); i++)
        {
            delete gameBoard[i];
            gameBoard[i] = nullptr;
        }
    }

    void showBoard(){
        cout << "B ";
        for (size_t i = 0; i < gameBoard.size(); i++)
        {
            cout << gameBoard[i]->getLetter() << " ";
            
        }
        cout << "F" << endl;
    }

    string getTileType(int n){
        return gameBoard[n]->getLetter();
    }
    tile* getTile(int n){
        return gameBoard[n];
    }
    
};