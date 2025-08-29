#include <iostream>
#include <vector>
#include "board.h"
#include "player.h"
#include "dice.h"
#include "turn.h"
using namespace std;

class gameType{
    protected:
    int tilesNum, playerNumber, Turns, stpBckSnk, stpAhdLddr;
    dice* gameDice;
    vector<Player*> Players;
    board* gameBoard;
    vector<Turn*> TurnList;

    public:
    gameType(int tilesNum, int playerNumber, int Turns, int snakeTiles,int ladderTiles, int stepBackSnake, int stepAheadLadder):
    tilesNum(tilesNum), playerNumber(playerNumber), Turns(Turns), stpBckSnk(stepBackSnake), stpAhdLddr(stepAheadLadder){
        gameDice = new dice();
        gameBoard = new board(tilesNum,snakeTiles,ladderTiles);
        for (size_t i = 0; i < playerNumber; i++)
        {
            Players.push_back(new Player(i+1)); // crea los players
        }
    };
    virtual void gameStart() = 0;
    ~gameType(){
        for (size_t i = 0; i < Players.size(); i++)
        {
            delete Players[i];
            Players[i] = nullptr;
        }
        for (size_t i = 0; i < TurnList.size(); i++)
        {
            delete TurnList[i];
            TurnList[i] = nullptr;
        }
        
        delete gameBoard;
        delete gameDice;

        gameBoard = nullptr;
        gameDice = nullptr;
    };
};

class Automatic : public gameType{
    public:
    Automatic(int tilesNum, int playerNumber, int Turns, int snakeTiles,int ladderTiles, int stepBackSnake, int stepAheadLadder):
    gameType(tilesNum, playerNumber, Turns, snakeTiles, ladderTiles, stepBackSnake, stepAheadLadder){}

    void gameStart() override {
        int n = 1, newtile, playerNum, dice;
        tile* targetTileP;
        string type;

        for (size_t i = 0; i < playerNumber; i++)
        {
            playerNum = Players[i]->getplayerNum();
            dice = gameDice->diceRoll();
            newtile = Players[i]->getTile();

            if (newtile + dice < tilesNum){
                type = gameBoard->getTileType(newtile + dice - 2); 
                targetTileP = gameBoard->getTile(newtile + dice - 2);

                if(type == "S"){
                    newtile = *targetTileP + stpBckSnk;  // SOBRECARGA DE OPERADOR
                }
                else if(type == "L"){
                    newtile = *targetTileP + stpAhdLddr;  // SOBRECARGA DE OPERADOR
                }
                else{
                    newtile = *targetTileP + 0;
                }
            }
            else{
                newtile = tilesNum;
                type = "F";
            }
            if(newtile >= tilesNum){
                newtile = tilesNum;
            }
            else if (newtile <= 1){
                newtile = 1;
                type = "B";
            }
            
            TurnList.push_back(new Turn(n, playerNum, Players, dice, type, newtile, *gameBoard));

            Players[i]->setTile(newtile);

            cout << *TurnList[n-1];
            
            cout << "---------------------------------------------------" << endl;
            // lo que se imprime en consola
            if(newtile >= tilesNum){
                    cout << "-- GAME OVER --\nPlayer " << playerNum << " is the winner!!!" << endl;
                    break; // ganador
            }
            n += 1;
            if(i == playerNumber - 1)
            {
                i = -1;
            }
        }
    }

};

class Manual : public gameType{
    public:
    Manual(int tilesNum, int playerNumber, int Turns, int snakeTiles,int ladderTiles, int stepBackSnake, int stepAheadLadder):
    gameType(tilesNum, playerNumber, Turns, snakeTiles, ladderTiles, stepBackSnake, stepAheadLadder){}

    void gameStart() override {
        int n = 1, newtile = 1, playerNum, dice, errCount = 0;
        tile* targetTileP;
        string opt, type;

        cout << "Press C to continue next turn, or E to end the game: " << endl;
            for (size_t i = 0; i < playerNumber; i++)
            {
                playerNum = Players[i]->getplayerNum();
                cin >> opt;
                
                if(opt == "E"){
                    cout << "-- GAME OVER --\nThanks for playing!!!";
                    break;
                }
                else if(n > Turns){
                    cout << "-- GAME OVER --\nThe maximum number of turns has been reached...";
                    break;
                }
                else if(opt == "C"){
                    playerNum = Players[i]->getplayerNum();
                    dice = gameDice->diceRoll();
                    newtile = Players[i]->getTile();

                    if (newtile + dice < tilesNum){
                        type = gameBoard->getTileType(newtile + dice - 2); 
                        targetTileP = gameBoard->getTile(newtile + dice - 2);

                    if(type == "S"){
                        newtile = *targetTileP + stpBckSnk; // SOBRECARGA DE OPERADOR
                    }
                    else if(type == "L"){
                        newtile = *targetTileP + stpAhdLddr; // SOBRECARGA DE OPERADOR 
                    }
                    else{
                        newtile = *targetTileP + 0;
                    }
                }
                else{
                    newtile = tilesNum;
                    type = "F";
                }
                if(newtile >= tilesNum){
                    newtile = tilesNum;
                }
                else if (newtile <= 1){
                    newtile = 1;
                    type = "B";
                }

                    TurnList.push_back(new Turn(n, playerNum, Players, dice, type, newtile, *gameBoard));

                    Players[i]->setTile(newtile);

                    cout << *TurnList[n-1];

                    cout << "---------------------------------------------------" << endl;
                    // lo que se imprime en consola
                    if(newtile >= tilesNum){
                        cout << "-- GAME OVER --\nPlayer " << playerNum << " is the winner!!!" << endl;
                        break; // ganador
                    }   
                    n += 1;
                }
                else{
                    try{
                        throw runtime_error("Invalid option");
                    }
                    catch (const runtime_error& e){
                        if (errCount > 5)
                        {
                            cout << "-- GAME OVER --\nInvalid menu choice exceeded";
                            break;
                        }
                        errCount += 1;
                        i -= 1;
                        cout << e.what() << " press C to continue next turn, or E to end the game: " <<  endl;
                        continue;
                    }
                }
                if (i == playerNumber - 1)
                {
                    i = -1;
                }
            }
    }
};