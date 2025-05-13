#include "Cat.h"
#include <iostream>
#include <fstream>
using namespace std;

Cat::Cat() : Pet(), scratch_lvl(50) {
    happy_lvl = 25;
    sleepy_lvl = 70;
    bored_lvl = 60;
}

bool Cat::save_file(const string &fileName) const {
    ofstream outFile(fileName); 
    if (!outFile) {
        return false;  // File failed to open
    }
    outFile << name << " " << type << " " << hunger_lvl << " "
        << happy_lvl << " " << bored_lvl << " " << cleanliness_lvl << " "
        << sleepy_lvl << " " << satisfaction << " " << scratch_lvl << " " << endl;
    return true;
}

bool Cat::load_file(const string &fileName) {
    ifstream inFile(fileName);
    if(!inFile) {
        cout << "Could not load file." << endl;
        return false;  // File failed to open
    }
    inFile >> name >> type >> hunger_lvl >> happy_lvl >> bored_lvl >> cleanliness_lvl >> 
        sleepy_lvl >> satisfaction >> scratch_lvl; 
    inFile.close(); // Close the file
    return true; 
}

bool Cat::delete_file(const string &fileName) {
    if(remove(fileName.c_str()) == 0) {
        return true; // File deleted successfully
    }
    return false; 
}

void Cat::Feed() {
    if(hunger_lvl >= 30) {
        hunger_lvl -= 20;
        happy_lvl += 10;
        satisfaction += 10;
        cout << name << " happily eats and hunger level is now " << hunger_lvl << "." << endl;
        nextHour(1);
    }
    else {
        cout << name << " is full and doesn't want more food." << endl;
        happy_lvl -= 5;
        satisfaction -= 2;
    }
    ClampValue(hunger_lvl, 0, 100);
}

void Cat::Rest() {
    if(sleepy_lvl <= 30) {
        cout << name << " is not tired and does not want to go to sleep." << endl;
        satisfaction-= 5;
        return;
    }

    if(sleepy_lvl >= 45) {
        cout << name << " is sleepy and is now going to sleep." << endl;
        satisfaction += 8;
    }

    cout << name << " is now sleeping";
    for (int i = 0; i < 3; ++i) {  // Loop to simulate sleep
        cout << ".";
        for (int j = 0; j < 50; ++j) {}
    }
    cout << " ᶻ 𝗓 𐰁..." << endl;
    nextHour(5);
    sleepy_lvl = 0;
    satisfaction+= 10;
    cout << name << " is now fully rested!" << endl;
    ClampValue(sleepy_lvl, 0, 100);
}

// decreases how bored the pet is and increases happiness  
void Cat::Cuddle() {
    if(bored_lvl >= 50) {  
        bored_lvl -= 6;
        happy_lvl += 8;
        satisfaction += 5;
        cout << name << " is happy after cuddling! Boredom reduced to " << bored_lvl << ".";
        nextHour(1);
    }
    else {
        cout << name << " doesn't feel like cuddling right now." << endl;
    }
    ClampValue(bored_lvl, 0, 100);
    cout << endl;
}  

void Cat::Observe() {
    if(bored_lvl >= 30 && happy_lvl >= 30) {
        bored_lvl -= 1;
        satisfaction += 2;
        observeCount++;
        cout << name << " is happy to have your attention \\(•◡•)//" << endl;
    }
    
    if(observeCount >= 7) {
        cout << name << " does not want to be observed anymore." << endl;
        satisfaction -= 1;
        bored_lvl += 3;
        return;
    }
    cout << endl;
    ClampValue(bored_lvl, 0, 100);

}

// decreases cleanliness_lvl   
void Cat::CleanUp() {
    
    if(cleanliness_lvl >= 20) {
        happy_lvl+= 8; 
        cleanliness_lvl -= 20;
        satisfaction+= 13;
        cout << name << "'s place is now cleaner! The level is now " << cleanliness_lvl << endl << endl;
        nextHour(1);
    }
    else {
        satisfaction -= 3;
        cout << name << "'s place is already pretty clean." << endl;
    }
    ClampValue(cleanliness_lvl, 0, 100); 
    cout << endl;
}

void Cat::scratchPost() {
    if(scratch_lvl >= 50 && bored_lvl >= 50) {
        scratch_lvl -= 15;
        hunger_lvl += 5;
        bored_lvl -= 7;
        happy_lvl += 10;
        satisfaction += 5;
        // reword this next statement 
        cout << name << " is happy to scratch the post! Now " << name << "'s want to scratch something is ";
        cout << scratch_lvl << endl;
        
        cout << "   |\\---/|" << endl;
        cout << "   | ,_, |" << endl;
        cout << "    \\_`_/-..----." << endl;
        cout << " ___/ `   ' ,""+   \\  " << endl;
        cout << "(__...'   __\\    |`.___.';" << endl;
        cout << "  (_,...'(_,.`__)/'.....+" << endl;
    }
    else {
        cout << name << " doesn't feel like scratching anything right now." << endl;
    }
}


// This interaction increases/decreases values to reflect a cat playing with a laser.  
void Cat::chaseLaser() {
   if(bored_lvl <= 25) {
    cout << name << " doesn't feel like chasing a laser right now. Maybe later though!" << endl;
    return;
   }
   else {
    cout << "        (`. " << endl;
    cout << "         ) ) " << endl;
    cout << "        ( ( " << endl;
    cout << "         \\ \\ " << endl;
    cout << "          \\ \\ " << endl;
    cout << "        .-'  `-. " << endl;
    cout << "       /        `. " << endl;
    cout << "      (      )    `-._ ,    _ " << endl;
    cout << "       )   ,'         (.\\--'( " << endl;
    cout << "       \\  (         ) /      \\ " << endl;
    cout << "        \\  \\_(     / (    <6 (6 " << endl;
    cout << "         \\_)))\\   (   `._  .:Y)__ " << endl;
    cout << "          '''  \\   `-._.'`---^_))) " << endl;
    cout << "                `-._ )))       ``` " << endl;
    cout << "                     ```           hjw " << endl;

    scratch_lvl -= 10;
    hunger_lvl += 10;
    bored_lvl -= 20;
    happy_lvl += 12;
    satisfaction += 7;
    cout << name << " had a lot of fun chasing the laser!" << endl;
    nextHour(1);
   }
}

void Cat::catJungle() {
    if(bored_lvl <= 25 && cleanliness_lvl >= 60) {
        cout << name << " doesn't feel like playing on the cat jungle right now. Maybe later though!" << endl;
        return;
    }
    else {
        scratch_lvl -= 5;
        hunger_lvl += 8;
        bored_lvl -= 18;
        happy_lvl += 15;
        satisfaction += 9;

        cout << name << " had a lot of fun on the cat jungle! Good job making this choice." << endl;
        cout << endl;
        cout << "  ╱|、♡" << endl;
        cout << " (` -7" << endl;
        cout << " |、⁻〵" << endl;
        cout << " じしˍ,)ノ" << endl;
        nextHour(2);
        cout << endl;
    // print figure below

   }
}

void Cat::takeNap() {
    if(sleepy_lvl >= 50) {
        cout << name << " is not tired enough to take a nap!" << endl;
        satisfaction -= 2;
        return;
    }
    else {
        cout << endl;
        cout << "   |\\      _,,,---,,_" << endl;
        cout << "   /,`.-'`'    -.  ;-;;,_" << endl;
        cout << "  |,4-  ) )-,_..;\\ (  `'-'" << endl;
        cout << " '---''(_/--'  `-\\_)        Felix Lee" << endl;
        
        sleepy_lvl -= 35;
        hunger_lvl += 15;
        scratch_lvl += 8;
        satisfaction += 10;
        cout << name << " takes a cat nap and is now feeling refreshed!" << endl << endl;;
        
        cout << "             _,'|             _.-''``-...___..--';)" << endl;
        cout << "           /_ \\'.      __..-' ,      ,--...--'''" << endl;
        cout << "          <\\    .`--'''       `     /'" << endl;
        cout << "           `-';'               ;   ; ;" << endl;
        cout << "     __...--''     ___...--_..'  .;.'" << endl;
        cout << "    (,__....----'''       (,..--''" << endl;
        nextHour(3);
    }
}

void Cat::walk() {  
    if(bored_lvl >= 65 && hunger_lvl <= 50) {
        bored_lvl -= 30;
        scratch_lvl -= 12;
        happy_lvl += 23;
        satisfaction += 15;
        cout << name << " is ready for a walk with you!" << endl;
        
        // print figure 
        cout << "   /\\_/\\ " << endl;
        cout << "   >^.^<.---." << endl;
        cout << "  _'-`-'     )\\" << endl;
        cout << " (6--\\ |--\\ (`.`-." << endl;
        cout << "     --'  --'  ``-'BP" << endl;
        nextHour(2);

    }
    else {
        cout << name << " doesn't feel like going on a walk." << endl;
    }
}

void Cat::nextHour(int hours) {
    hunger_lvl += (5 * hours); 
    sleepy_lvl += (8 * hours);  
    bored_lvl += (6 * hours);  
    happy_lvl -= (2 * hours);
    cleanliness_lvl += (1 * hours);  
    satisfaction -= (1 * hours); 
    scratch_lvl += (3 * hours);

    ClampValue(hunger_lvl, 0, 100);
    ClampValue(sleepy_lvl, 0, 100);
    ClampValue(bored_lvl, 0, 100);
    ClampValue(happy_lvl, 0, 100);
    ClampValue(cleanliness_lvl, 0, 100);
    ClampValue(satisfaction, 0, 100);
    ClampValue(scratch_lvl, 0, 100);
    cout << endl; 
    if(hunger_lvl >= 65) { 
        cout << name << " is hungry, please feed them!" << endl; 
    }
    if(bored_lvl >= 75) {
        cout << name << " requires some attention, please play with them!" << endl;
    }
    
    cout << hours << " hour(s) have passed and " << name << "'s stats have now changed." << endl;

    if(satisfaction <= 0) {
        if(!LoseGame()) {  // If LoseGame() returns false, exit the function
            return;
        }
    }
    cout << endl;
}

void Cat::DisplayStats() {
    Pet::DisplayStats();
    string divider = "─────── ♡ ──────";
    cout << "Scratching urge: " << scratch_lvl << endl << divider << endl;
    cout << endl;
}

void Cat::PrintOptions(bool &isPlaying) {
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
        cout << "➤ Scratch a post (7)" << endl;
        cout << "➤ Chase a laser (8)" << endl;
        cout << "➤ Play on the cat jungle (9)" << endl;
        cout << "➤ Take a nap (10)" << endl;
        cout << "➤ Take a walk (11)" << endl;
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


void Cat::doAction(int option,bool &isPlaying) {
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
            scratchPost();
            break;
        case 8:
            chaseLaser();
            break;
        case 9:
            catJungle();
            break;
        case 10:
            takeNap();
            break;
        case 11:
            walk();
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


