#include "Horse.h"
#include <iostream>
#include <fstream>
using namespace std;

Horse::Horse() : Pet(), riding_lvl(50), horseShoe_lvl(100) {
    happy_lvl = 75;
    bored_lvl = 65;
    satisfaction = 70;
}

bool Horse::save_file(const string &fileName) const {
    ofstream outFile(fileName); 
    if (!outFile) {
        return false;  // File failed to open
    }
    outFile << name << " " << type << " " << hunger_lvl << " "
        << happy_lvl << " " << bored_lvl << " " << cleanliness_lvl << " "
        << sleepy_lvl << " " << satisfaction << " " << riding_lvl << " " << horseShoe_lvl << endl;
    return true;
}

bool Horse::load_file(const string &fileName) {
    ifstream inFile(fileName);
    if (!inFile) {
        cout << "Could not load file." << endl;
        return false;  // File failed to open
    }
    inFile >> name >> type >> hunger_lvl >> happy_lvl >> bored_lvl >> cleanliness_lvl >> 
        sleepy_lvl >> satisfaction >> riding_lvl >> horseShoe_lvl; 
    inFile.close(); // Close the file
    return true; 
}

bool Horse::delete_file(const string &fileName) {
    if(remove(fileName.c_str()) == 0) {
        return true; // File deleted successfully
    }
    return false; 
}

void Horse::Feed() {
    if(hunger_lvl >= 50) {
        hunger_lvl -= 35;
        happy_lvl += 12;
        satisfaction += 8;
        cout << name << " happily eats and hunger level is now " << hunger_lvl << "." << endl;
        nextHour(2);
    }
    else {
        cout << name << " is full and doesn't want more food." << endl;
        happy_lvl -= 6;
        satisfaction -= 4;
    }
    ClampValue(hunger_lvl, 0, 100);

}

void Horse::Rest() {
    if(sleepy_lvl <= 35) {
        cout << name << " is not tired and does not want to go to sleep." << endl;
        satisfaction-= 5;
        return;
    }

    if(sleepy_lvl >= 65) {
        cout << name << " is sleepy and is now going to sleep." << endl;
        satisfaction += 8;
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
    cout << name << " is now fully rested!" << endl;
    ClampValue(sleepy_lvl, 0, 100);

}

// decreases how bored the pet is and increases happiness  
void Horse::Cuddle() {
    if(bored_lvl >= 50) {  
        bored_lvl -= 15;
        happy_lvl += 15;
        satisfaction += 10;
        cout << name << " is happy after cuddling! Boredom reduced to " << bored_lvl << ".";
        nextHour(1);
    }
    else {
        cout << name << " doesn't feel like cuddling right now." << endl;
    }
    cout << endl;
    ClampValue(bored_lvl, 0, 100);

}  

void Horse::Observe() {
    if(bored_lvl >= 30 && happy_lvl >= 30) {
        bored_lvl -= 3;
        satisfaction += 2;
        observeCount++;
        cout << name << " is happy to have your attention \\(•◡•)//" << endl;
    }
    if(observeCount >= 3) {
        cout << name << " does not want to be observed anymore." << endl;
        satisfaction -= 2;
        bored_lvl += 5;
        return;
    }
    ClampValue(bored_lvl, 0, 100);
    cout << endl;
}

// decreases cleanliness_lvl   
void Horse::CleanUp() {    
    if(cleanliness_lvl >= 50) {
        happy_lvl+= 8; 
        cleanliness_lvl -= 20;
        satisfaction+= 13;
        cout << name << "'s place is now cleaner! The level is now " << cleanliness_lvl << endl << endl;
        nextHour(1);
        ClampValue(cleanliness_lvl, 0, 100); 

    }
    else {
        satisfaction -= 3;
        cout << name << "'s place is already pretty clean." << endl;
    }
}

// Allows the player to groom the horse, increasing sociability, happiness, satisfaction, and riding eagerness values. 
void Horse::Groom() {
    happy_lvl += 15;
    riding_lvl += 20;
    horseShoe_lvl += 15;
    satisfaction += 10;
    cout << name << " is now all cleaned up!" << endl;
    nextHour(1);
}

// increasing happiness and reducing boredom. It can only be performed if the horse is not hungry. 
void Horse::Practice() {
    if(hunger_lvl <= 50) {
        cout << name << " is too hungry to practice. Please feed them!" << endl;
        return;
    }
    else {
        happy_lvl += 20;
        bored_lvl -= 25;
        satisfaction += 5;
        riding_lvl -= 10;
        sleepy_lvl -= 25;
        hunger_lvl += 28;
        horseShoe_lvl -= 20;
        cout << name << " is excited to jump through some hurdles!" << endl;
        // prints out figure
        cout << " ~,  O" << endl;
        cout << " /)\\~_/\\\\" << endl;
        cout << "'  \\ \\~_\\__ ~" << endl;
        cout << "  _|_)_\\_( )~~~" << endl;
        cout << "//   /|   \\|\\" << endl;
        cout << "  ()//|     \\`" << endl;
        cout << "  ||/||" << endl;
        cout << "  ||" << endl;
        cout << "  ||" << endl;
        nextHour(2);
    }
}

// increases/decrease various private variables (both in the pet class and in the horse class).     
void Horse::Ride() {
    if(riding_lvl <= 30 && hunger_lvl >= 20) {
        cout << name<< " doesn't feeling going on a ride yet and they're too hungry to go on a ride. Please feed them." << endl;
        return;
    }
    else {
        happy_lvl += 30;
        bored_lvl -= 30;
        satisfaction += 8;
        riding_lvl -= 10;
        horseShoe_lvl -= 25;
        hunger_lvl += 20;
        sleepy_lvl -= 25;
        
        cout << name << " is ready to go a ride with you! Safe travels!" << endl;
        nextHour(2);
        // print figure
        cout << "        {)" << endl;
        cout << "   _,  _/)" << endl;
        cout << "  /,`\"/.|),___" << endl;
        cout << " (\\.'//`<-'  ,`+." << endl;
        cout << "   `'_|  >  /  |))" << endl;
        cout << "    (.-)|--'\\ < \\(" << endl;
        cout << "     \\)||    ||  `" << endl;
        cout << "       /(    /( " << endl;
        ClampValue(riding_lvl, 0, 100);
    }
    cout << endl;
}

// is dependent on the horseShoe_lvl value. 
void Horse::changeHorseShoe() {
    if(horseShoe_lvl >= 75) {
        cout << name << "'s horse shoes don't need to be changed yet." << endl;
    }
    else {
        horseShoe_lvl += 25;
        riding_lvl += 30;
        hunger_lvl += 20;
        satisfaction += 10;
        sleepy_lvl -= 10;
        cout << name << " is happy that you changed their horse shoes and can't wait to go on a ride together!" << endl;
        
        cout << "   >>\\." << endl;
        cout << "   /_  )`." << endl;
        cout << "  /  _)`^)`.)   _.---. _" << endl;
        cout << " (_,,' \\  `^-)\"\"      `.\\ " << endl;
        cout << "       |              | \\" << endl;
        cout << "       \\              / |" << endl;
        cout << "      / \\  /.___.'\\  (\\ (_" << endl;
        cout << "     < ,\"||     \\ |`. \\`-'" << endl;
        cout << "      \\\\ ()      )|  )/" << endl;
        cout << "  hjw |_>|>     /_] //" << endl;
        cout << "       /_]        /_]" << endl;
        nextHour(1);
        ClampValue(horseShoe_lvl, 0, 100);

    }
    cout << endl;
}

// This interaction allows the player to feed the horse a snack and can decrease their hunger level slightly.  
void Horse::giveSnack() {
    
    if(hunger_lvl <= 30) {
        happy_lvl -= 2;
        cout << name << " is feeling full and doesn't want a snack." << endl;
        return;
    }
    else {
        hunger_lvl -= 5;
        riding_lvl += 5;
        cout << name << " gladly accepts the snack and eats it!" << endl;
        
        cout << "      /\\/\\" << endl;
        cout << "     /    \\" << endl;
        cout << "   ~/(^  ^)" << endl;
        cout << "  ~/  )  (" << endl;
        cout << " ~/   (  )" << endl;
        cout << "~/     ~~" << endl;
        cout << "~/       |" << endl;
    }
    cout << endl;
} 


void Horse::nextHour(int hours) {
    hunger_lvl += (3 * hours); 
    sleepy_lvl += (6 * hours);  
    bored_lvl += (10 * hours);  
    happy_lvl -= (7 * hours);
    cleanliness_lvl += (4 * hours);  
    satisfaction -= (3 * hours); 
    riding_lvl += (5 * hours);
    horseShoe_lvl -= (1 * hours);

    ClampValue(hunger_lvl, 0, 100);
    ClampValue(sleepy_lvl, 0, 100);
    ClampValue(bored_lvl, 0, 100);
    ClampValue(happy_lvl, 0, 100);
    ClampValue(cleanliness_lvl, 0, 100);
    ClampValue(satisfaction, 0, 100);
    ClampValue(riding_lvl, 0, 100);
    ClampValue(horseShoe_lvl, 0, 100);   


    if(hunger_lvl >= 50) {
        cout << name << " is hungry, please feed them!" << endl;
    }
    else if(bored_lvl >= 60) {
        cout << name << " requires some attention, please play with them!" << endl;
    }
    else {
        cout << hours << " hour(s) have passed and " << name << "'s stats have now changed." << endl;
    }
    
    if(satisfaction <= 0) {
        if(!LoseGame()) {  // If LoseGame() returns false, exit the function
            return;
        }
    }
}   

void Horse::DisplayStats() {

    string divider = "─────── ♡ ──────";
    Pet::DisplayStats();
    cout << "Riding eagerness " << riding_lvl << endl << divider << endl;
    cout << "Horse shoes condition " << horseShoe_lvl << endl << divider << endl;
    cout << endl;
}

//need to edit to ask to enter another number with yes or no
void Horse::PrintOptions(bool &isPlaying) {
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
        cout << "➤ Groom (7)" << endl;
        cout << "➤ Practice (8)" << endl;
        cout << "➤ Go on a ride (9)" << endl;
        cout << "➤ Change horse shoes (10)" << endl;
        cout << "➤ Give a snack (11)" << endl;
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

void Horse::doAction(int option,bool &isPlaying) {
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
            Groom();
            break;
        case 8:
            Practice();
            break;
        case 9:
            Ride();
            break;
        case 10:
            changeHorseShoe();
            break;
        case 11:
            giveSnack();
            break;
        case 12:
            cout << "Would you like to continue playing or exit?" << endl;
            cout << "➤ Continue playing (1)" << endl
                << "➤ Exit to main menu (2)" << endl;
            cin >> response;

            while(response < 1 || response > 2) {
                cout << "Invalid choice. Enter 1 to continue playing or 2 to exit: ";
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

