#include "Pet.h"
#include <iostream>
#include <fstream>
#include <cstdio>
using namespace std;

Pet::Pet() { 
    hunger_lvl = 50;
    sleepy_lvl = 50;  
    bored_lvl = 50;  
    happy_lvl = 50; 
    cleanliness_lvl = 50;    
    satisfaction = 100; 
    name = "Unknown"; 
    type = "Unknown"; 
    observeCount = 0;
}

// outputs a welcome message to the player.  
void Pet::PrintWelcomeMsg() {  
    cout << endl;
    cout << "┏━━━━━━ʕ•㉨•ʔ━━━━━┓" << endl;
    cout << "    Purrfect Pal   " << endl;
    cout << "┗━━━━━━⋆⋅☆⋅⋆━━━━━━┛" << endl;
    cout << endl;
} 

bool Pet::save_file(const string &fileName) const {
    ofstream outFile(fileName); 
    if(!outFile) {
        return false;  // File failed to open
    }
    outFile << name << " " << type << " " << hunger_lvl << " "
        << happy_lvl << " " << bored_lvl << " " << cleanliness_lvl << " "
        << sleepy_lvl << " " << satisfaction << " " << endl;
    return true;
}

bool Pet::load_file(const string &fileName) {
    ifstream inFile(fileName);
    if(!inFile) {
        return false;  // File failed to open
    }
    inFile >> name >> type >> hunger_lvl >> happy_lvl >> bored_lvl >> cleanliness_lvl >> 
        sleepy_lvl >> satisfaction; 
    inFile.close(); // Close the file
    return true; 

}

bool Pet::delete_file(const string &fileName) {
    if(remove(fileName.c_str()) == 0) {
        return true; // File deleted successfully
    }
    return false; 
}


// Handles new game and load game decisions + which pet type they want for their game file. 
bool Pet::InitializeGame() { 
    int option, petType;
    string retry;
    
    string divider = "─── ⋆⋅☆⋅⋆ ───";
    cout << "would you like to: " << endl;
    cout << "➤ start a new game" << endl;
    cout << "➤ continue playing" << endl;
    cout << "➤ delete saved game" << endl; 
    cout << "➤ exit game" << endl << divider << endl;

    cout << "To start a new game, enter 1!" << endl;
    cout << "To continue playing a game, enter 2!" << endl;
    cout << "To delete a saved game, enter 3!" << endl;
    cout << "To exit the game, enter 4!" << endl << divider << endl;
    cout << "Enter your choice: " << endl;

    cin >> option;
    while(option < 1 || option > 4) {
        cout << "Oops, it looks like the number you entered wasn't valid. Please enter a valid number (1-4): " << endl;
        cin >> option;
        break;
    } 

    switch(option) {
        case 1: {
            cout << "Please enter a name for the file: ";
            cin >> fName;
            cout << "The name you entered is " << fName << endl;

            cout << "What would you like to name your pet?" << endl;
            cin.ignore(); // Clear newline from input buffer
            getline(cin, name);

            cout << "Your pet's name is " << name << endl;

            if(save_file(fName)) {
                cout << "The file with the name " << fName << " has now been created!" << endl;

                // Prompt for the pet type after the game is created
                int petOption;
                do {
                    cout << "To confirm, please re-select your pet type: " << endl
                         << "➤ horse" << endl
                         << "➤ cat" << endl
                         << "➤ bird" << endl;
                    cout << "Enter 1 for horse. Enter 2 for cat. Enter 3 for bird." << endl;
                    cin >> petOption;

                    if(petOption == 1) {
                        type = "Horse";
                        return true;
                    } 
                    else if(petOption == 2) {
                        type = "Cat";
                        return true;
                    } 
                    else if(petOption == 3) {
                        type = "Bird";
                        return true;
                    } 
                    else {
                        cout << "Error! Please enter 1, 2, or 3." << endl;
                        continue; // Repeat if the input is invalid
                    }
                } while(true);
            } 
            else {
                cout << "Error: Could not create " << fName << endl;
                return false; // Initialization failed
            }
        }
        case 2: {
            bool fileLoaded = false;
            do {
                cout << "Enter the name of the save file you wish to load: ";
                cin >> fName;

                if(load_file(fName)) {
                    cout << "File was found and is now opening!" << endl << endl;
                    cout << name << " is happy to see you!" << endl;
                    fileLoaded = true;
                    return true; // Initialization successful
                } 
                else {
                    cout << "Error: File was not found. Would you like to enter another name? (yes/no): ";
                    cin >> retry;

                    if(retry == "no" || retry == "No") {
                        cout << "Returning to main menu." << endl;
                        return false; // Initialization failed
                    }
                }
            } while(!fileLoaded);
            return false; // Should not reach here unless there's an error
        }
        case 3: {
            bool fileDeleted = false;
            do {
                cout << "Enter the name of the save file you wish to delete: ";
                cin >> fName;

                if(delete_file(fName)) {
                    cout << "The file " << fName << " has now been deleted." << endl;
                    cout << "Returning to main menu." << endl;
                    fileDeleted = true; // File deletion successful
                    return false; // Exit to main menu
                } 
                else {
                    cout << "Error: File was not found or could not be cleared. Would you like to enter another name? (yes/no): ";
                    cin >> retry;

                    if(retry == "no" || retry == "No") {
                        cout << "Returning main menu." << endl;
                        return false; // Initialization failed
                        exit(0);
                    }
                }
            } while(!fileDeleted);
            return false; // Should not reach here unless there's an error
        }
        case 4: {
            cout << "Now exiting the program." << endl;
            exit(0); // Exit the program
            return false;
        }
        default:
            cout << "Invalid option. Please enter a number between 1 and 4." << endl;
            return false; // Initialization failed
    }
}

void Pet::ClampValue(int &value, int min, int max) {
    if (value < min) {
        value = min;
    } else if (value > max) {
        value = max;
    }
}

void Pet::Feed() {
    ClampValue(hunger_lvl, 0, 100);

    if(hunger_lvl >= 50) {
        hunger_lvl -= 20;
        happy_lvl += 10;
        satisfaction += 5;
        cout << name << " happily eats and hunger level is now " << hunger_lvl << "." << endl;
    }
    else {
        cout << name << " is full and doesn't want more food." << endl;
        happy_lvl -= 5;
        satisfaction -= 3;
    }
}

void Pet::Rest() {
    ClampValue(sleepy_lvl, 0, 100);

    if(sleepy_lvl <= 35) {
        cout << name << " is not tired and does not want to go to sleep." << endl;
        satisfaction-= 5;
        return;
    }

    if(sleepy_lvl >= 75) {
        cout << name << " is sleepy and is now going to sleep." << endl;
        satisfaction += 8;
    }
    else { 
        cout << name << " feels tired and decides to go to bed." << endl;
    }

    cout << name << " is now sleeping";
    for (int i = 0; i < 3; ++i) {  // Loop to simulate sleep
        cout << ".";
        for (int j = 0; j < 50; ++j) {}
    }
    cout << " ᶻ 𝗓 𐰁..." << endl;
    nextHour(4);
    sleepy_lvl = 0;
    satisfaction+= 10;
    cout << name << " is now fully rested and ready for the day!" << endl;
}

// decreases how bored the pet is and increases happiness  
void Pet::Cuddle() {
    ClampValue(bored_lvl, 0, 100);

    if(bored_lvl >= 50) {  
        bored_lvl -= 10;
        happy_lvl += 12;
        satisfaction += 8;
        cout << name << " is happy after cuddling! Boredom reduced to " << bored_lvl << ".";
    }
    else {
        cout << name << " doesn't feel like cuddling right now." << endl;
    }
    cout << endl;
}  

void Pet::Observe() {
    ClampValue(bored_lvl, 0, 100);
    if(bored_lvl >= 50) {
        bored_lvl -= 3;
        satisfaction += 5;
        observeCount++;
        cout << name << " is happy to have your attention \\(•◡•)//" << endl;
    }
    
    if(observeCount >= 5) {
        cout << name << " does not want to be observed anymore." << endl;
        satisfaction -= 2;
        bored_lvl += 5;
        return;
    }
    cout << endl;
}

// resets observeCount after the game closes. 
void Pet::ResetObsCount() {
    observeCount = 0;
}

// decreases cleanliness_lvl   
void Pet::CleanUp() {
    ClampValue(cleanliness_lvl, 0, 100); 
    
    if(cleanliness_lvl >= 50) {
        happy_lvl+= 7; 
        cleanliness_lvl -= 15;
        satisfaction+= 10;
        cout << name << "'s place is now cleaner! The level is now " << cleanliness_lvl << endl << endl;
    }
    else {
        satisfaction -= 3;
        cout << name << "'s place is already pretty clean." << endl;
    }
}

void Pet::DisplayStats() {
    string divider = "─────── ♡ ──────";
    cout << name << "'s current stats: " << endl;
    cout << "Hunger: " << hunger_lvl << endl << divider << endl;
    cout << "Happiness: " << happy_lvl << endl << divider << endl;
    cout << "Boredom: " << bored_lvl << endl << divider << endl;
    cout << "Cleanliness: " << cleanliness_lvl << endl << divider << endl;
    cout << "Sleepiness: " << sleepy_lvl << endl << divider << endl;
    cout << "Satisfaction: " << satisfaction << endl << divider << endl;
}

// increases/decreases all the integer members while player is playing
void Pet::nextHour(int hours) {
    hunger_lvl += (3 * hours); 
    sleepy_lvl += (5 * hours);  
    bored_lvl += (10 * hours);  
    happy_lvl -= (5 * hours);
    cleanliness_lvl += (5 * hours);  
    satisfaction -= (3 * hours);

    ClampValue(hunger_lvl, 0, 100);
    ClampValue(sleepy_lvl, 0, 100);
    ClampValue(bored_lvl, 0, 100);
    ClampValue(happy_lvl, 0, 100);
    ClampValue(cleanliness_lvl, 0, 100);
    ClampValue(satisfaction, 0, 100);

    if(hunger_lvl > 50) {
        cout << name << " is hungry, please feed them!" << endl;
    }
    else if(bored_lvl > 70) {
        cout << name << " wants some attention, please play with them!" << endl;
    }
    if(satisfaction <= 0) {
        if(!LoseGame()) {  // If LoseGame() returns false, exit the function
            return;
        }
    }
    cout << endl;
}

void Pet::RestartGame() {
    fName.clear(); // Clear the file name or reset it as necessary
    *this = Pet();
    InitializeGame(); // Restart the game by re-running the initialization function
}

bool Pet::LoseGame() {
    int response;
    string retry;

    if(satisfaction <= 0) {
        cout << "Uh oh! It looks like " << name << " is no longer happy and has left you! .·°՞(≧□≦)՞°·." << endl;
        cout << "Game Over. Would you like to try again or exit the game?" << endl;
        cout << "Enter 1 to restart the game or 2 to leave the game." << endl;
        cin >> response;

        while(response < 1 || response > 2) {
            cout << "Oops, it looks like the number you entered wasn't valid. Please enter a valid number (1-2): " << endl;
            cin >> response;
            cout << "Would you like to enter another number? (yes/no): " << endl;
            cin >> retry;
            
            if(retry == "no" || retry == "No") {
                exit(0);
            }
        }

        if(response == 1) {
            RestartGame();
        }
        else {
            cout << "Thanks for playing! Now exiting the program." << endl;
            save_file(fName);
            exit(0);
            return false;
        }
        return true;
    }
    return false;
}

void Pet::PrintOptions(bool &isPlaying) {
    int option; 
    string retry;
    while(true) {
        cout << endl;
        cout << "What would you like to do?" << endl;
        cout << "➤ Display stats (1)" << endl;
        cout << "➤ Feed (2)" << endl;
        cout << "➤ Rest (3)" << endl;
        cout << "➤ Cuddle (4)" << endl;
        cout << "➤ Observe (5)" << endl;
        cout << "➤ Clean up (6)" << endl;
        cout << "➤ Exit the game (7)" << endl;
        cout << "Enter the number that matches the interaction you want." << endl;
        cin >> option;
        if(option >= 1 && option <= 7) {
            doAction(option, isPlaying); // Pass isPlaying to doAction
            if(option == 7) {
                return;
            }
        } else {
            cout << "Not a valid option. Please enter a valid number (1-7)." << endl;
            cout << "Would you like to enter another number? (yes/no): " << endl;
            cin >> retry;

            if(retry == "no" || retry == "No") {
                exit(0);
            }
        }
    }
}

void Pet::doAction(int option, bool &isPlaying) {
    int response; 
    switch(option) {
        case 1: 
            DisplayStats();
            break;
        case 2:
            Feed();
            nextHour(1);
            break;
        case 3: 
            Rest();
            nextHour(3); 
            break;
        case 4:
            Cuddle();
            nextHour(1);
            break;
        case 5: 
            Observe();
            nextHour(1);
            break;
        case 6:
            CleanUp();
            nextHour(1);
            break;
        case 7:
            cout << "Would you like to continue playing or exit?" << endl; 
            cout << "➤ Continue playing (1)" << endl 
                 << "➤ Exit to main menu (2)" << endl;
            cin >> response;

            while(response < 1 || response > 2) {
                cout << "Invalid choice. Enter 1 to continue playing or 2 to exit: ";
                cin >> response;
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
                isPlaying = false; // Exit the outer loop
            }
            return;

        default:
            cout << "Invalid option. Please select a valid action." << endl;
            break;
    }
}

void Pet::RunGame() {
    bool isPlaying = true;
    
    if(!InitializeGame()) {
        cout << "Failed to initialize the game. Exiting..." << endl;
        return; // Exit RunGame if initialization fails
    }
    // Main game loop
    while(isPlaying) {
        // Check if the game should continue playing
        if(LoseGame()) {
            continue; // Handle losing condition if necessary
        }

        // Print options and handle user interaction
        PrintOptions(isPlaying);

        // Exit the loop if the file name (fName) is empty, indicating the game is over
        if(fName.empty()) {
            isPlaying = false;
        }
    }

    cout << "Thanks for playing and see you soon!" << endl;
}



