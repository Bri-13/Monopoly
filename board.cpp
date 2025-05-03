#include <iostream>
#include "board.h"
#include <cstdlib>

using namespace std;

Board::Board(int playerNum){
    int h=0;
    for(int i = 0; i < 40; i++)
    {
        if(i%10==0) displayBoxes_[i].setSet(-1);
        if(i==0) board.push_back(new Start());
        else if(i==10) board.push_back(new Jail());
        else if(i==20) board.push_back(new Parking());
        else if(i==30) board.push_back(new GoJail());
        else if(i%5==1 || i%5 ==3)
        {
            board.push_back(new House((h/3), h, (60 + (h/3)*20), (h*2)));
            displayBoxes_[i].setSet(h/3+1);
            h++;
        }
        else if(i%5==4)
        {
            board.push_back(new House((h/3), h, (80 + (h/3)*20), (h*2+2)));
            displayBoxes_[i].setSet(h/3+1);
            h++;
        }
        else
        {
            board.push_back(new Cards());
            displayBoxes_[i].setSet(0);
        } 
    }

    for(int i = 0; i<playerNum; i++){
        playerLocation.push_back(0);
        playerOrder.push_back(new Player(i));
        displayBoxes_[0].setPlayer(i);
    }

    playerNum_ = playerNum;
    turn_ = 0;
}

Board::~Board(){
    for(int i = 0; i < 40; i++){
        delete board[40-1-i];
        board.pop_back();
    }

    for(int i = 0; i < playerNum_; i++){
        delete playerOrder[4-1-i];
        playerOrder.pop_back();
    }
}

void Board::display()const{
    int i1, i2;
    for(int row=0; row<11; row++)
    {
        // printing first row along with set.
        if(row==0)
        {
            cout <<"   ";
            for(int i=10; i>=0; i--)
                cout << displayBoxes_[20+i].printSet()
                    << displayBoxes_[20+i].printSet() << " ";
            cout<< endl<< "   " ;
            for(int i=10; i>=0; i--)
                cout << displayBoxes_[20+i].printTop();
            cout<< endl<< "   " ;
            for(int i=10; i>=0; i--)
                cout << displayBoxes_[20+i].printBottom();
            cout<< endl;
            i1 = 19;
            i2 = 31;
            continue;
        }

        // printing final row with set
        if(row==10)
        {
            cout <<"   ";
            for(int i=0; i<11; i++)
                cout << displayBoxes_[i].printTop();
            cout<< endl<< "   " ;
            for(int i=0; i<11; i++)
                cout << displayBoxes_[i].printBottom();
            cout<< endl<< "   " ;
            for(int i=0; i<11; i++)
                cout << displayBoxes_[i].printSet()
                    << displayBoxes_[i].printSet() << " ";
            cout<< endl;
            continue;
        }
        

        // prints top part of display or blank space
        for(int top=0; top<11; top++)
        {
            // blank space
            if(top!=0 && top!=10)
            {
                cout << "     ";
                continue;
            }
            // set if first col
            if(top==0)
            {
                cout << displayBoxes_[i2].printSet() << " ";
                cout << displayBoxes_[i2].printTop();
            } 
            // set if last col
            if(top==10)
            {
                cout << displayBoxes_[i1].printTop();
                cout << displayBoxes_[i1].printSet();
            }
        }

        cout << endl;

        // prints bottom part of display or blank space
        for(int bottom=0; bottom<11; bottom++)
        {
            // blank space
            if(bottom!=0 && bottom!=10)
            {
                cout << "     ";
                continue;
            }
            // set if first col
            if(bottom==0)
            {
                cout << displayBoxes_[i2].printSet() << " ";
                cout << displayBoxes_[i2].printBottom();
                i2++;
            } 
            // set if last col
            if(bottom==10)
            {
                cout << displayBoxes_[i1].printBottom();
                cout << displayBoxes_[i1].printSet();
                i1--;
            }
        }

        cout<< endl;
    }
    cout<< endl;
}

void Board::printMenu() const{
    cout << "Options:" << endl;
    cout << "===============================" << endl;
    cout << "QUIT:                0" << endl;
    cout << "SELL HOUSE:          1" << endl;
    cout << "ROLL DICE:           2" << endl;
    cout << "DISPLAY PLAYER STAT: 3" << endl;
    cout << "===============================" << endl;
}

int Board::roll(){
    srand( time(NULL));
    int result = rand()%5 + 1 + rand()%5 + 1;
    return result;
}

void Board::changePlayerLocation(int index){
    // if execute does not return 0, change the player's
    // location to what execute returned
    if(index){
        displayBoxes_[playerLocation[turn_]].setPlayer(turn_);
        playerLocation[turn_] = index;
        displayBoxes_[playerLocation[turn_]].setPlayer(turn_);
        this -> display();
    }
}

void Board::playerAdvance(int dice){
    cout << playerOrder[turn_] << " is moving forward by " << dice << " !" << endl;
    displayBoxes_[playerLocation[turn_]].setPlayer(turn_);
    playerLocation[turn_] += dice;
    if(playerLocation[turn_] >= 40){
        playerLocation[turn_] -= 40;
        board[0] -> execute(playerOrder[0]);
    }
    displayBoxes_[playerLocation[turn_]].setPlayer(turn_);

}

Grid* Board::getCurr(){
    return board[playerLocation[turn_]];
}

Player* Board::getPlayer(){
    return playerOrder[turn_];
}

int Board::getTurn(){
    return turn_;
}

void Board::increaseTurn(){
    turn_++;
    turn_ = turn_ % playerNum_;
}

void Board::printCurrPlayer()const{
    playerOrder[turn_] -> playerStat();
}

Player* Board::calculateWinner()const{
    Player* winner;
    int totalMax = -1;
    for(int i = 0; i < playerNum_; i++){
         vector<House*> currentHouse = playerOrder[i] -> houseOwn();
         int total = playerOrder[i] -> getBudget();
         for(size_t j = 0; j < currentHouse.size(); j++){
            total += (currentHouse[j] -> getPrice()) * 1.2;
         }

         if(totalMax < total){
            winner = playerOrder[i];
            totalMax = total;
         }
    }
    
    return winner;
}

