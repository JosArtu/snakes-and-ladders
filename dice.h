#include <iostream>
#include <cstdlib> 

using namespace std;

class dice{
    public:
    dice(){
        srand(time(0));
    }
    int diceRoll(){
        return rand() % 6 + 1;
    }
};