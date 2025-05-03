#ifndef PLAYER_H
#define PLAYER_H
#include<vector>
#include<iostream>
#include "grid.h"

class House;

class Player{
public: 
    Player(int id);
    ~Player();
    bool sell(House* sell);
    void changeBudget(int change);  // setter
    void changeFreeJail(int change);   // setter
    int getBudget();  // getter
    int getFreeJail();   // getter
    void changeInJail(); 
    bool getInJail(); 
    void playerStat() const;
    void buyHouse(House* house);
    bool checkMonopoly()const;
    int getMonopolyID()const;
    const std::vector<House*> houseOwn()const;
    friend std::ostream& operator<<(std::ostream& ostr, const Player* op);
    friend std::ostream& operator<<(std::ostream& ostr, const std::vector<House*> op);

private: 
    int budget;
    int id_;
    std::vector<House*> own;
    bool inJail; //Change to false if true before skip
    int jailFree;
    bool hasMonopoly;
    int monopolyID; 
};

#endif
