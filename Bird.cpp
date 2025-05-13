#include "Bird.h"
#include <fstream>
#include <iostream>
#include <random>
using namespace std;

Bird::Bird() : Pet(), flight_lvl(50) {
    happy_lvl = 60;
    bored_lvl = 60;
}

bool Bird::save_file(const string &fileName) const {
    ofstream outFile(fileName); 
    if (!outFile) {
        return false;  // File failed to open
    }
    outFile << name << " " << type << " " << hunger_lvl << " "
        << happy_lvl << " " << bored_lvl << " " << cleanliness_lvl << " "
        << sleepy_lvl << " " << satisfaction << " " << flight_lvl << " " << endl;
    return true;
}

bool Bird::load_file(const string &fileName) {
    ifstream inFile(fileName);
    if(!inFile) {
        cout << "Could not load file." << endl;
        return false;  // File failed to open
    }
    inFile >> name >> type >> hunger_lvl >> happy_lvl >> bored_lvl >> cleanliness_lvl >> 
        sleepy_lvl >> satisfaction >> flight_lvl; 
    inFile.close(); // Close the file
    return true; 
}

bool Bird::delete_file(const string &fileName) {
    if(remove(fileName.c_str()) == 0) {
        return true; // File deleted successfully
    }
    return false; 
}

void Bird::Feed() {
    if(hunger_lvl >= 20) {
        hunger_lvl -= 35;
        happy_lvl += 18;
        satisfaction += 15;
        cout << name << " happily eats and hunger level is now " << hunger_lvl << "." << endl;
        nextHour(1);
    }
    else {
        cout << name << " is full and doesn't want more food." << endl;
        happy_lvl -= 3;
        satisfaction -= 3;
    }
    ClampValue(hunger_lvl, 0, 100);
}

void Bird::Rest() {
    if(sleepy_lvl <= 35) {
        cout << name << " is not tired and does not want to go to sleep." << endl;
        satisfaction-= 5;
        return;
    }

    if(sleepy_lvl >= 55) {
        cout << name << " is sleepy and is now going to sleep." << endl;
        satisfaction += 8;
    }

    cout << name << " is now sleeping";
    for (int i = 0; i < 3; ++i) {  // Loop to simulate sleep
        cout << ".";
        for (int j = 0; j < 50; ++j) {}
    }
    cout << " ᶻ 𝗓 𐰁..." << endl;
    nextHour(3);
    sleepy_lvl = 0;
    satisfaction+= 10;
    cout << name << " is now fully rested!" << endl;
    ClampValue(sleepy_lvl, 0, 100);
}

// decreases how bored the pet is and increases happiness  
void Bird::Cuddle() {
    if(bored_lvl >= 50) {  
        bored_lvl -= 10;
        happy_lvl += 10;
        satisfaction += 8;
        cout << name << " is happy after cuddling! Boredom reduced to " << bored_lvl << ".";
        nextHour(1);
    }
    else {
        cout << name << " doesn't feel like cuddling right now." << endl;
    }
    ClampValue(bored_lvl, 0, 100);
    cout << endl;
}  

void Bird::Observe() {
    if(bored_lvl >= 45 && happy_lvl >= 40) {
        bored_lvl -= 5;
        satisfaction += 7;
        observeCount++;
        cout << name << " is happy to have your attention \\(•◡•)//" << endl;
    }
    
    if(observeCount >= 10) {
        cout << name << " does not want to be observed anymore." << endl;
        satisfaction -= 2;
        bored_lvl += 5;
        return;
    }
    cout << endl;
    ClampValue(bored_lvl, 0, 100);

}

// decreases cleanliness_lvl   
void Bird::CleanUp() {
    if(cleanliness_lvl >= 20) {
        happy_lvl+= 12; 
        cleanliness_lvl -= 18;
        satisfaction+= 8;
        cout << name << "'s place is now cleaner! The level is now " << cleanliness_lvl << endl;
        nextHour(1);
    }
    else {
        satisfaction -= 5;
        cout << name << "'s place is already pretty clean." << endl;
    }
    ClampValue(cleanliness_lvl, 0, 100); 
    cout << endl;
}

// Interaction where the bird flies around, decreasing flight_lvl & boredom while increasing other values. 
void Bird::fly() {
    if(flight_lvl >= 30 && bored_lvl >= 50) { 
        flight_lvl += 25;
        hunger_lvl += 6;
        bored_lvl -= 15;
        cleanliness_lvl += 8;
        happy_lvl += 12;
        satisfaction += 7;
        sleepy_lvl += 12;

        cout << "    ------------------------------------------------ " << endl;
        cout << "                      ___" << endl;
        cout << "                  _,-' ______" << endl;
        cout << "                .'  .-'  ____7" << endl;
        cout << "               /   /   ___7" << endl;
        cout << "             _|   /  ___7" << endl;
        cout << "           >(')\\ | ___7     jgs" << endl;
        cout << "             \\\\/     \\_______" << endl;
        cout << "             '        _======>" << endl;
        cout << "             `'----\\\\`" << endl;
        cout << "    ------------------------------------------------ " << endl;
        nextHour(1);
    }
    else {
        cout << name << " isn't ready to go on a fly yet." << endl;
    }
    ClampValue(flight_lvl, 0, 100); 
}

// Interaction where the bird solves a puzzle, increasing/decreasing values based on the puzzle-solving experience.  
// edit: I changed this a bit & it has to be a cap of a certain # of times it's selected until it's no longer enjoyable for the bird
void Bird::puzzleSolve() {
    if(bored_lvl >= 45 && hunger_lvl <= 30) {
        happy_lvl += 5;
        bored_lvl -= 25;
        hunger_lvl += 8;
        satisfaction += 3;
        cleanliness_lvl += 2;
        sleepy_lvl += 7;
        cout << name << " is now solving a puzzle!" << endl;
        cout << name << "'s boredom level is now " << bored_lvl << " and chirps happily after solving the puzzle!" << endl;
        // print figure
        cout << "   (" << endl;
        cout << "  `-`-." << endl;
        cout << "  '( @ >" << endl;
        cout << "   _) (" << endl;
        cout << "  /    )" << endl;
        cout << " /_,'  / " << endl;
        cout << "   \\  / " << endl;
        cout << "===m\"\"m===" << endl;
        cout << endl;
        nextHour(2);
        
    }
    else {
        cout << name << " doesn't want to solve a puzzle right now." << endl;
    }
    ClampValue(bored_lvl, 0, 100); 
    ClampValue(happy_lvl, 0, 100); 

} 

void Bird::printInstructions() {
    cout << endl;
    cout << "To play this game, you must sucessfully guess where " << name << " is." << endl;
    cout << "You can guess by selecting a number from 1-3. If you select the right number," << endl;
    cout << "then you win the game. Otherwise, you lose the game." << endl;
    cout << "Be aware, every time you lose " << name << " gets unhappier every time, along with more stat changes." << endl;
}

// The player must find the bird   
void Bird::hideAndSeek() {
    int min = 1;
    int max = 3;
    int guess, response;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(min, max);
    int randomValue = distrib(gen);
    string response2; 
    cout << "Would you like to see the instructions on how to play this minigame? (yes/no)" << endl;
    cin >> response2; 
    if(response2 == "yes" || response2 == "Yes") {
        printInstructions();
    }
    
    if(bored_lvl >= 55 && hunger_lvl <= 30) {
        bored_lvl -= 15;
        flight_lvl += 3;
        sleepy_lvl += 4;
        hunger_lvl -= 2;
        nextHour(1);
        cout << "Please enter a number from 1-3: " << endl;
        cin >> guess;
    
        if(guess == randomValue) {
            cout << "You won this round and congratulations on finding your bird successfully!" << endl;
            happy_lvl += 25;
            satisfaction += 5;
            cout << "    .--.\n"
            "    /( @ >    ,-.\n"
            "   / ' .'--._/  /\n"
            "   :   ,    , .'\n"
            "   '. (___.'_/\n"
            "    ((-((-''mrf\n";
        }
        else {
            cout << "Oh no, you didn't win this round, better luck next time!" << endl;
            happy_lvl -= 15;
            satisfaction -= 5;

        }
    }
    else {
        cout << name << " does not want to play hide and seek right now. Try again later." << endl;
    }
}

// A memory matching game where the player matches cards.
void Bird::MatchingGame() {
    int min = 1;
    int max = 5;
    int guess, response;
    int guessCount = 0;
    
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(min, max);
    int randomValue = distrib(gen);
    
    if(bored_lvl >= 45 && hunger_lvl <= 30 && happy_lvl >= 20) {
        bored_lvl -= 27;
        happy_lvl += 20;
        satisfaction += 16;
        cout << name << " is ready to play a round of matching objects!" << endl;
        cout << "To play, you must guess the same number from 1-5 as " << name << " to gain a point." << endl;
        cout << "You will have 5 rounds. Be sure to try to win so that " << name << " will be in good spirits!" << endl;
        for(int i = 0; i < 5; i++) {
            cout << "Enter a number from 1-5: " << endl;
            cin >> response;
            guessCount++;
            if(response == randomValue) {
                cout << "You got this one right!" << endl;
                happy_lvl += 5;
                cout << "    ,~" << endl;
                cout << "   ('v)__" << endl;
                cout << "  (/ (``/)" << endl;
                cout << "   \\__>' hjw" << endl;
                cout << "    ^^" << endl;
            }
            else {
                cout << "Better luck next time!" << endl;
                happy_lvl -= 5;
            }
        }
    nextHour(2);
    }
    else {
        cout << name << " isn't feeling up to playing matching objects right now." << endl;
    }
} 

// The bird sings which increases happiness and sociability, if stimulation is high enough. 
void Bird::sing() {
    if(happy_lvl >= 50) {
        cout << name << " lets out a happy chirp!" << endl;
    }
    else {
        cout << name << " lets out a low chirp." << endl;
    }
}

void Bird::nextHour(int hours) {
    hunger_lvl += (3* hours); 
    sleepy_lvl += (6 * hours);  
    bored_lvl += (8 * hours);  
    happy_lvl -= (4 * hours);
    cleanliness_lvl += (1 * hours);  
    satisfaction -= (2 * hours); 
    flight_lvl += (5 * hours);

    ClampValue(hunger_lvl, 0, 100);
    ClampValue(sleepy_lvl, 0, 100);
    ClampValue(bored_lvl, 0, 100);
    ClampValue(happy_lvl, 0, 100);
    ClampValue(cleanliness_lvl, 0, 100);
    ClampValue(satisfaction, 0, 100);
    ClampValue(flight_lvl, 0, 100);
    cout << endl; 
    
    if(hunger_lvl >= 45) { 
        cout << name << " is hungry, please feed them!" << endl; 
    }
    if(bored_lvl >= 50) {
        cout << name << " requires some attention, please play with them!" << endl;
    }
    
    cout << hours << " hour(s) have passed and " << name << "'s stats have now changed." << endl;

    if(satisfaction <= 0) {
        if(!LoseGame()) {  // If LoseGame() returns false, exit the function
            return;
        }
    }
}

// Displays all stats, including both inherited and other variables.  
void Bird::DisplayStats() {
    Pet::DisplayStats();
    string divider = "─────── ♡ ──────";
    cout << "Flight eagerness: " << flight_lvl << endl << divider << endl;
    cout << endl;
}    

void Bird::PrintOptions(bool &isPlaying) {
    int option; 
    string retry;

    while(true) {
        cout << "What would you like to do?" << endl;
        cout << "➤ Display stats (1)" << endl;
        cout << "➤ Feed (2)" << endl;
        cout << "➤ Rest (3)" << endl;
        cout << "➤ Cuddle (4)" << endl;
        cout << "➤ Observe (5)" << endl;
        cout << "➤ Clean up (6)" << endl;
        cout << "➤ Go on a flight (7)" << endl;
        cout << "➤ Solve a puzzle (8)" << endl;
        cout << "➤ Play hide & seek (9)" << endl;
        cout << "➤ Play a matching game (10)" << endl;
        cout << "➤ Sing (11)" << endl;
        cout << "➤ Exit the game (12)" << endl; 
        cout << endl;
        cout << "To make a choice, please enter the number that matches the interaction you want!" << endl;

        cin >> option;
        if(option >= 1 && option <= 12) {
            doAction(option,isPlaying);
            if(option == 12) {
                return;
            }
        }
        else {
            cout << "Not a valid option. Please enter a valid number (1-12)." << endl;
            cout << "Would you like to enter another number? (yes/no): " << endl;
            cin >> retry;
            if(retry == "no" || retry == "No") {
                return;
            }
        }
    }
} 
 

void Bird::doAction(int option,bool &isPlaying) {
    int response; 
    string retry;

    switch(option) {
        case 1: 
            DisplayStats();
            break;
        case 2:
            Feed();
            break;
        case 3: 
            Rest();
            break;
        case 4:
            Cuddle();
            break;
        case 5: 
            Observe();
            break;
        case 6:
            CleanUp();
            break;
        case 7: 
            fly();
            break;
        case 8:
            puzzleSolve();
            break;
        case 9:
            hideAndSeek();
            break;
        case 10:
            MatchingGame();
            break;
        case 11:
            sing();
            break;
        case 12:
            cout << "Would you like to continue playing or exit?" << endl;
            cout << "➤ Continue playing (1)" << endl
                << "➤ Exit to main menu (2)" << endl;
            cin >> response;

            while(response < 1 || response > 2) {
                cout << "Invalid choice. Enter 1 to continue playing or 2 to exit. ";
                cin >> response;
                cout << "Would you like to enter another number? (yes/no): " << endl;
                cin >> retry;

                if(retry == "no" || retry == "No") {
                    return;
                }
            }

            if(response == 2) {
                if(save_file(fName)) {
                    cout << "Game saved successfully!" << endl; 
                } 
                else {
                    cout << "Error saving game!" << endl;
                }
            fName.clear();  
            ResetObsCount();
            cout << "Now exiting the game and returning to main menu!" << endl;
            isPlaying = false; // Exit the outer loop and return to the main menu
            return; // This return ensures that you exit this case block properly
        }
        break;  

        default:
            cout << "Invalid option. Please select a valid action." << endl;
            break; 
    }
}

