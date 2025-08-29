#include "myGame.h"
#include <iostream>
using namespace std;


int main()
{
    int tilesNum, playerNumber, Turns, snakeTiles, ladderTiles, stepBackSnake, stepAheadLadder,type, opt;
    cout << "Default settings = 0\nCustom settings = 1" << endl;
    cin >> opt;
    if (opt == 1)
    {
        cout << "Tiles number: ";
        cin >> tilesNum;
        cout << "Player number: ";
        cin >> playerNumber;
        cout << "Turns: ";
        cin >> Turns;
        cout << "Snaketiles: ";
        cin >> snakeTiles;
        cout << "Laddertiles: ";
        cin >> ladderTiles;
        cout << "Step back snake: ";
        cin >> stepBackSnake;
        cout << "Step ahead ladder: "; 
        cin >> stepAheadLadder;
        cout << "Manual = 1, automatic = 2: ";
        cin >> type;
        try {
            MyGame g(tilesNum,snakeTiles,ladderTiles,stepBackSnake,stepAheadLadder,playerNumber,Turns,type);
            g.startGame();
        }
        catch (const runtime_error& e) {
            std::cout << "Error: " << e.what() << std::endl;
            return 1;
        }
    }
    else{
        MyGame g(30,3,3,3,3,2,20,1);
        g.startGame();
    }

}