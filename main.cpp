#include <iostream>
#include "board.h"

using namespace std;

int MAX = 10000;

int main(int argc, char* argv[]){
    if(argc < 2){
        cout << "Please provide the number of players" << endl; 
        return 1;
    }

    if(atoi(argv[1]) < 2){
        cout << endl << "There needs to be a minimum of 2 players" << endl;
        return 1;
    }

    if(atoi(argv[1]) > 4){
        cout << endl << "There cannot be more than 4 players" << endl;
        return 1;
    }

    int x = atoi(argv[1]);
    Board b(x);

    int userInput = -1;
    b.display();

    while(true){
        cout << "......................................." << endl;
        if(b.getPlayer() -> getInJail()){
            cout << b.getPlayer() << " is in jail, your turn has been skipped" << endl;
            b.getPlayer() -> changeInJail();
            b.increaseTurn();
            cout << "Hand it over to " << b.getPlayer() << endl;
            continue;
        }
        
        b.printMenu();
        cout << "Enter a command: " << endl;
        cin >> userInput;

        try{
            if(cin.fail()){
                cin.clear();
                cin.ignore(250, '\n');
                //throw exception
                throw invalid_argument("Please enter a valid input (0-4).");
            }
            if(userInput == 0){
                //End the programme
                cout << "Programme Quit" << endl;
                break;
            } 

            if(userInput == 1){
                //Sell house
                size_t houseInput, houseID;
                vector<House*> myHouse = b.getPlayer() -> houseOwn();
                if(!myHouse.empty()){
                    //If the player owns a house
                    cout << "You own the following property: " << endl;
                    for(size_t i = 0; i < myHouse.size(); i++){
                        cout << "=============" << i+1 << "=============" << endl;
                        cout << myHouse[i] << endl;
                    }
                    cout << "Choose the house you'd like to sell and input the number attached on top of the house information. " 
                         << "If wish to go back enter 0." << endl;

                    cin >> houseInput;
                    if(cin.fail()){
                        cin.clear();
                        cin.ignore(250, '\n');
                        //throw exception
                        throw invalid_argument("Please enter a valid input (0-).");
                        //After throwing exception how do we know the player can come back to this? 
                    }

                    if(houseInput == 0){
                        cout << "You're back to menu" << endl;
                        continue;
                    }

                    while(houseInput > myHouse.size() || houseInput <= 0){
                        cout << "Please enter a valid number of the house you wish to sell or 0 to go back" << endl;
                        cin >> houseInput;
                        if(cin.fail()){
                            cin.clear();
                            cin.ignore(250, '\n');
                            houseInput=-1;
                        }
                    }

                    houseID = myHouse[houseInput-1] -> getID();

                    if(!(b.getPlayer() -> sell(myHouse[houseInput-1]))){
                        cout << "There was an error in selling House." << houseID << endl;
                    }
                }

                else{
                    //If the player doesn't own a house
                    cout << b.getPlayer() << " does not own a house. Please select a different option." << endl;
                }
            }

            else if(userInput == 2){
                b.playerAdvance(b.roll());
                b.display();
                b.changePlayerLocation(b.getCurr() -> execute(b.getPlayer()));
                cout << b.getPlayer() << "'s turn ends: Hand it over to ";
                b.increaseTurn();
                cout << b.getPlayer() << endl;
            }

            else if(userInput == 3){
                b.printCurrPlayer();
            }

            else{
                b.printMenu();
                cout << "Please enter a valid input from 0-3" << endl;
                continue;
            }

            if(b.getPlayer() -> getBudget() > MAX){
                cout << b.getPlayer() << "'s maximum budget has reached. The game will terminate" << endl;
                break;
            }
        }

        catch(invalid_argument& e){
            b.printMenu();
            cout << e.what() << endl;
            continue;
        }
    }

    Player* winner = b.calculateWinner();
    cout << winner << " has won this game! Congrats!" << endl;
    return 0;
}
