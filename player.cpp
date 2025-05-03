#include <iostream>
#include<vector>
#include "player.h"
#include "grid.h"

using namespace std;

Player::Player(int id){
    id_ = id;
    budget = 1500;
    own.resize(0);
    inJail = false;
    jailFree = 0;
    hasMonopoly = false;
    monopolyID = -1;
}

Player::~Player(){}

void Player::changeBudget(int change){
    budget += change;
    cout << "Player " << id_ << "'s remaining budget: " << budget << endl;
}

bool Player::sell(House* sell){
    bool owned = false;
    int index = -1;
    int count = 0;
    for(size_t i = 0; i < own.size(); i++){
        if(sell == own[i]){
            owned = true;
            index = i;
            count++;
        }
        else if(sell -> getType() == own[i] -> getType()){
            count++;
        }
    }

    if(owned){
        int input;
        if(count == 3){
            cout << "You have a Monopoly in this set. Are you sure you want to sell it?" << endl;
            cout << "Enter 1 to confirm, 2 otherwise" << endl;
            cin >> input;
            while(cin.fail()){
                cout << "Enter 1 to confirm, 2 otherwise" << endl;
            }
        }

        if(input == 1){
            budget += own[index]->getPrice();
            own.erase(own.begin()+index-1);
            hasMonopoly = false;
            return true;
        }
        
        else{
            return false;
        }
    }

    else{
        return false;
    }
}

void Player::changeFreeJail(int change){
    jailFree += change;
}

int Player::getBudget(){
    return budget;
}

int Player::getFreeJail(){
    return jailFree;
}

void Player::changeInJail(){
    inJail = !inJail;
}

bool Player::getInJail(){
    return inJail;
}

const vector<House*> Player::houseOwn()const{
    return own;
}

ostream& operator<<(ostream& ostr, const vector<House*> op){
    if(op.empty()){
        ostr << "EMPTY";
    }
    else{
        for(size_t i = 0; i < op.size(); i++){
            ostr << op[i];
        }
    }
    return ostr;
}

void Player::playerStat() const{
    cout << "--------------------------------------------"<< endl;
    cout << "Player " << id_ << "'s Stats: " << endl;
    cout << "Budget: " << budget << endl;
    cout << "List of houses owned: " << endl << own << endl;
    cout << "The number of Jail Free card: " << jailFree << endl;
    cout << "--------------------------------------------"<< endl;
}

ostream& operator<<(ostream& ostr, const Player* op){
    ostr << "Player " << op -> id_;
    return ostr;
}

void Player::buyHouse(House* house){
    budget -= house -> getPrice();
    cout << "Remaining budget: " << budget << endl;
    own.push_back(house);
    int count = 1;
    for(size_t i = 0; i < own.size(); i++){
        if(own[i] -> getType() == house -> getType()){
            count++;
        }
    }

    if(count == 3){
        hasMonopoly = true;
        monopolyID = house -> getType();
        cout << this << "now has a Monopoly with set " << house -> getType() << "!. The rent price for these houses will go up" << endl; 
    }
}

bool Player::checkMonopoly()const{
    return hasMonopoly;
}
int Player::getMonopolyID()const{
    return monopolyID;
}

