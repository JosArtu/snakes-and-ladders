#include <iostream>
using namespace std;

class tile{
    protected:
    int tileNumber;
    string letter;

    public:
    tile(int tlNb):tileNumber(tlNb){};

    virtual int operator+(int n) = 0;

    int getTileNum(){
        return tileNumber;
    }

    string getLetter(){
        return letter;
    }

    
};



class normalTile : public tile{
    public:
    normalTile(int tlnum):tile(tlnum){
        letter = "N";
    }
    int operator+(int n) override{
        return this->getTileNum() + n;
    }

};

class ladderTile : public tile{
    public:
    ladderTile(int tlnum):tile(tlnum){
        letter = "L";
    }
    int operator+(int n) override{
        return this->getTileNum() + n;
    }

};

class serpentTile : public tile{
    public:
    serpentTile(int tlnum):tile(tlnum){
        letter = "S";
    }
    int operator+(int n) override{
        return this->getTileNum() - n;
    }
};
