#ifndef GRID_H
#define GRID_H

#include <vector>
#include <string>
#include <iostream>
#include "player.h"

class Player;

// abstract base class
class Grid{
public: 
    Grid();
    virtual ~Grid();
    virtual int execute(Player* cPlayer) = 0;

private: 
    std::vector <std::string> cPlayer_;
};

class Cards: public Grid{
public: 
    Cards();
    ~Cards();
    int execute(Player* curr);
};

class House: public Grid{
public: 
    House();
    ~House();
    House(int set, int id, int price, int rent);
    int execute(Player* cPlayer);
    int getPrice()const;
    int getType()const;
    Player* getOwner();
    int getID();
    friend std::ostream& operator<<(std::ostream& ostr, const House*);

private: 
    int houseType_;
    int houseID_;
    int price_;
    int rent_;
    Player* owner_;
};

class Jail: public Grid{
public: 
    int execute(Player* cPlayer);
    Jail();
    ~Jail();
};

class Parking: public Grid{
public:
    int execute(Player* cPlayer);
    Parking();
    ~Parking();   
};

class GoJail: public Grid{
public: 
    GoJail();
    ~GoJail();
    int execute(Player* cPlayer);
};

class Start: public Grid{
public: 
    Start();
    ~Start();
    int execute(Player* cPlayer);    
};

class GoParking: public Grid{
    public: 
    int execute(Player* cPlayer);
    GoParking();
    ~GoParking();
};

#endif
