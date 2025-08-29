#include <iostream>
#include <vector>

using namespace std;

class Turn{
    private:
    int turnNum, playerNum, playerTile, Dice, Newtile;
    string Type;  
    vector<Player*> &Players;
    board &Board;

    public:
    Turn(int turnNum, int playerNum, vector<Player*>& Players, int Dice, string Type, int Newtile, board &Board): 
    turnNum(turnNum), playerNum(playerNum),Players(Players), Dice(Dice), Type(Type), Newtile(Newtile), Board(Board){
        playerTile = Players[playerNum - 1]->getTile();
    }

    friend ostream& operator<<(ostream& os, const Turn& Turn){
        cout << Turn.turnNum << ".-\tPlyr "<< Turn.playerNum << "\tTile " << Turn.playerTile << "\tDice " << Turn.Dice << "\tType " << Turn.Type << "\tNewtile " << Turn.Newtile << "\n" << endl;
        cout << "\t ";

        Turn.Board.showBoard();

        for (size_t o = 0; o < Turn.Players.size(); o++)
                {
                    cout << "Player" << o+1;
                    for (size_t v = 0; v < Turn.Players[o]->getTile(); v++)
                    {
                        cout << "  ";
                    }
                    cout << "X" << endl;
                }

        return os;
    }

};