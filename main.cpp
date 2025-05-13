#include "Pet.h"
#include "Pet.cpp"

#include "Horse.h"
#include "Horse.cpp"

#include "Cat.h"
#include "Cat.cpp"

#include "Bird.h"
#include "Bird.cpp"

#include <iostream>
using namespace std;

void Instructions() {
    cout << "The goal of this game is to take care of your new pet." << endl;
    cout << "There are various activities you can do with them." << endl << endl;
    
    cout << "Note: your pet may not always want to do what you want";
    cout << "when it comes to participating in activities." << endl;
    cout << endl;

    cout << "You lose the game when their satisfication hits 0,";
    cout << "so try your best to keep it from hitting 0." << endl << endl;

    cout << "You can choose what you want to do with your pet";
    cout << "by entering a number associated with the actions." << endl;
    cout << "Good luck and have fun!" << endl << endl;
}

int main() {
    Pet* pet = new Pet();
    pet->PrintWelcomeMsg();
    
    string response;

    cout << "Would you like the instructions before starting the game? (yes/no)" << endl;
    cin >> response;
    if(response == "yes" || response == "Yes") {
        Instructions();
        cout << "Alright, now let's get started!" << endl << endl;
    }
    else {
        cout << endl;
        cout << "Let's get started!" << endl;
    }
    cout << endl;
    cout << "Choose a pet type: " << endl
             << "➤ 1. Horse" << endl
             << "➤ 2. Cat" << endl
             << "➤ 3. Bird" << endl
             << "Enter the number corresponding to your choice: ";
    int type;
    cin >> type;

    if(type == 1) {
        pet = new Horse();
    } 
    else if(type == 2) {
        pet = new Cat();
    } 
    else if(type == 3) {
        pet = new Bird();
    }
    else {
        cout << "Invalid choice. Please enter a valid number (1-3)." << endl;
    }

    pet->RunGame();
    delete pet;
    pet = nullptr;
    return 0;
}
