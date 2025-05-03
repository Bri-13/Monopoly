#include <iostream>
#include <stdlib.h>
#include "grid.h"
#include "player.h"

const int JAIL = 10;
const int PARKING = 20;

using namespace std;
Grid::Grid(){}

Grid::~Grid(){}

int Cards::execute(Player* curr){
    cout << curr << " landed on Lucky Card!" << endl;

    srand(time(NULL));
    int outcome = rand() % 5;

    if(outcome == 0){
        //Change: 1. cPlayer status & cPlayer location
        cout << "This lucky card moves the player to Parking" << endl;
        GoParking temp;
        // temp.execute(curr);
        return temp.execute(curr);
    }

    else if(outcome == 1){
        cout << "This lucky card moves the player to Jail" << endl;
        GoJail temp1;
        // temp1.execute(curr);
        return temp1.execute(curr);
    }

    else if(outcome == 2){
        cout << "Congratulations! You picked up 100 on a street" << endl;
        curr -> changeBudget(100);
    }

    else if(outcome == 3){
        cout << "You got bitten by a dog. -100" << endl;
        curr -> changeBudget(-100);
    }

    else if(outcome == 4){
        cout << "You drew a Jail Free Card!" << endl;
        curr -> changeFreeJail(1);
    }

    return 0;
}

Cards::Cards(){
    
}

Cards::~Cards(){
    
}

House::House(){
    
}

House::~House(){
    
}

House::House(int set, int id, int price, int rent){
    houseType_ = set;
    houseID_ = id;
    price_ = price;
    rent_ = rent;
}

int House::execute(Player* curr){
    //If empty, option to buy. If not, cPlayer must pay
    if(owner_ == NULL){
        int answer = -1;
        cout << curr << " is at House " << houseID_ << endl;
        cout << "Here's the house stats: " << endl;
        cout << this << endl;
        if(curr->getBudget() < getPrice())
        {
            cout << curr << " does not have enough to buy, turn has ended" << endl;
            return 0;
        } 
        cout << "Would you like to buy this property?" << endl;
        cout << "0: Yes        1: No" << endl;
        cin >> answer;
        if(cin.fail()){
            // throw exception

        }
        if(!answer){
            curr -> buyHouse(this);
            owner_ = curr;
        }
    }
    else{
        if(owner_ == curr){
            cout << "You have landed on a property owned by yourself. No action needs to be taken" << endl;
            cout << "End of your turn." << endl;
        }

        else{
            cout << curr << " landed on " << owner_ << "'s property. You have to pay " << rent_ << " for rent" << endl;

            if(curr -> checkMonopoly() && (curr -> getMonopolyID() == houseID_)){
                cout << "Since " << owner_ << "has a monopoly in this set, your rent will go up" << endl;
            }

            else{
                cout << "You're renting this house. You have to pay " << price_ << endl;
                owner_ -> changeBudget(price_);
                owner_ -> changeBudget(price_ * -1);
            }
        }
    }

    return 0;
}

Jail::Jail(){

}

Jail::~Jail(){

}

int Jail::execute(Player* curr){
    // skip turn of cPlayer
    if(!(curr -> getInJail())){
        cout << curr << " is now visiting the jail" << endl;
        return 0;
    }
    cout << curr << " is in jail, your turn will be skipped next round" << endl;
    return JAIL;
}

Parking::Parking(){

}

Parking::~Parking(){}

int Parking::execute(Player* curr){
    cout << curr << " landed on parking" << endl;
    cout << "Congratulations! You get receive 200" << endl;
    curr -> changeBudget(200);
    return PARKING;
}

GoParking::GoParking(){

}

GoParking::~GoParking(){

}

int GoParking::execute(Player* curr){
    int input;
    cout << "Please type 1 to confirm this action" << endl;
    cin >> input;
    Parking temp;
    return temp.execute(curr);
}

GoJail::GoJail(){

}

GoJail::~GoJail(){

}

int GoJail::execute(Player* curr){
    if(curr -> getFreeJail()>0){
        curr -> changeFreeJail(-1);
        cout << "A get out of jail card has been used, you now have " << curr->getFreeJail();
        cout << " get out of jail cards left" << endl;
        return 0;
    }

    cout << "Please type 1 to confirm this action" << endl;
    int input;
    cin >> input;
    curr -> changeInJail();
    cout << curr << " has been moved to Jail" << endl;
    Jail temp;
    return temp.execute(curr);
}

Start::Start(){
    
}

Start::~Start(){

}

int Start::execute(Player* curr){
    cout << curr << " passed the start, player earns $200" << endl;
    curr -> changeBudget(200);
    return 0;
}

int House::getPrice()const{
    return price_;
}

int House::getType()const{
    return houseType_;
}

Player* House::getOwner(){
    return owner_;
}

ostream& operator<<(std::ostream& ostr, const House* op){
    ostr << "=====================" << endl;
    ostr << "id: " << op -> houseID_ << endl;
    ostr << "set: " << op -> houseType_ << endl;
    ostr << "rent: " << op -> rent_ << endl;
    ostr << "price: " << op -> price_ << endl;
    ostr << "=====================" << endl;
    return ostr;
}

int House::getID(){
    return houseID_;
}
