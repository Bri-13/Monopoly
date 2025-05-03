#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "grid.h"

struct DisplayItem{
    void setSet(int set)
    {
        set_ = set;
    }
    void setPlayer(int index)
    {
        players_[index] = !players_[index];
    }
    std::string printTop() const
    {   
        // const char* boardToString[] = { "\U00002B1B", "\U0001F534", "\U0001F7E1"}; 
        const char* boardToString[] = { "\U00002B1C", "\U0001F534", "\U0001F7E1"}; 
        std::string res;
        if(players_[0]) res+= boardToString[1];
        else res+= boardToString[0];
        if(players_[1]) res+= boardToString[2];
        else res+= boardToString[0];

        res+=" ";
        return res;
    }   
    std::string printBottom() const
    {
        // const char* boardToString[] = { "\U00002B1B", "\U0001F535", "\U0001F7E2"}; 
        const char* boardToString[] = { "\U00002B1C", "\U0001F535", "\U0001F7E2"}; 
        std::string res;
        if(players_[2]) res+= boardToString[1];
        else res+= boardToString[0];
        if(players_[3]) res+= boardToString[2];
        else res+= boardToString[0];

        res+=" ";
        return res;
    }   
    std::string printSet() const
    {
        const char* colors[] = { "\U0001F533", "\U0001F7E5", "\U0001F7E7", 
                                "\U0001F7E9", "\U0001F7E8",  "\U0001F7E6",
                                "\U0001F7EA", "\U00002B1B", "\U0001F7EB"};
        std::string res;
        if(set_==-1) res +="  ";
        else res+= colors[set_];
        return res;
    }


    int players_[4] = {0,0,0,0};
    int set_;
};


class Board{
public: 
    Board(int playerNum);
    ~Board();
    void display() const;
    void printMenu() const;
    const int JAIL = 10;
    const int PARKING = 20;
    void changePlayerLocation(int index);
    void playerAdvance(int dice);
    Grid* getCurr();
    Player* getPlayer();
    int getTurn();
    void increaseTurn();
    int roll();
    void printCurrPlayer()const;
    Player* calculateWinner()const;

private: 
    int maxCost;
    int turn_;
    int playerNum_;

    DisplayItem displayBoxes_[40];

    std::vector<Grid*> board;
    std::vector<Player*> playerOrder;
    std::vector<int> playerLocation;
};

#endif
