#pragma once
#include <string>
#include <iostream>
using namespace std;

class Pet {   
protected:
string name,type;
string fName; // holds name of file

int hunger_lvl,happy_lvl,
bored_lvl, cleanliness_lvl, sleepy_lvl, 
satisfaction, observeCount;

public:
Pet(); // default constructor that sets all integer members to 50 & name to “unknown”. 

virtual void Feed(); // decreases the hunger status, but if done repeatedly/when it’s full, it will not change the hunger status & decrease the happiness level. 
virtual void Rest(); // decreases the sleepiness status, cannot be chosen if it’s fully rested. It may also automatically go to sleep if it’s too tired to do anything.  
virtual void Cuddle(); // decreases how bored the pet is and increases happiness + sociability statuses.  
virtual void Observe(); // generally decreases how bored the pet is until a certain point is hit (and decreases sociability level). 
virtual void CleanUp(); // decreases cleanliness_lvl & increases sociability level.   

virtual void nextHour(int hours); // decreases/increases all the integer members while player is playing the game.

void ResetObsCount(); // resets the count
virtual void DisplayStats(); // Outputs the current values of all member variables.  

bool InitializeGame(); // Handles new game and load game decisions + which pet type they want for their game file. 
virtual bool save_file(const string &fileName) const; // checks whether a file was able to successfully save the pet's state to a file or not. 
virtual bool load_file(const string &fileName); // checks whether a file was able to successfully load the pet's state from a file or not. 
virtual bool delete_file(const string &fileName); // overwrites a file to "delete" it
void PrintWelcomeMsg(); // outputs a welcome message to the player.  
virtual void PrintOptions(bool &isPlaying); // handles the printing of the options and doing the options  
virtual void RunGame(); // actually runs the game.
virtual void doAction(int option, bool &isPlaying) ; // gets input from the user and does the action associated with the option selected. 
void ClampValue(int &value, int min, int max);
bool LoseGame(); 
void RestartGame();
virtual ~Pet() {};
};