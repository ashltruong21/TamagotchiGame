#pragma once
#include "Pet.h"
#include <iostream>
using namespace std;

class Horse: public Pet {
protected: 
int riding_lvl; // stores the value to represent how eager the horse is to go on a ride. 
int horseShoe_lvl; // to store the value of how clean or dirty the horse’s horseshoes are.  

public: 
Horse(); // default constructor riding level to 25, happiness_lvl to 75 and sociability to 100 and set the remaining variables to their default values in the Pet default constructor. 

void Feed() override; // decreases the hunger status, but if done repeatedly/when it’s full, it will not change the hunger status & decrease the happiness level. 
void Rest() override; // decreases the sleepiness status, cannot be chosen if it’s fully rested. It may also automatically go to sleep if it’s too tired to do anything.  
void Cuddle() override; // decreases how bored the pet is and increases happiness + sociability statuses.  
void Observe() override; // generally decreases how bored the pet is until a certain point is hit (and decreases sociability level). 
void CleanUp() override; 

void Groom(); // Allows the player to groom the horse, increasing sociability, happiness, satisfaction, and riding eagerness values. 
void Practice(); // Lets the horse practice navigating obstacles, increasing happiness and reducing boredom. It can only be performed if the horse is not hungry. 
void Ride(); // This interaction lets the player take the horse on a ride, and increases/decrease various private variables (both in the pet class and in the horse class). 
void changeHorseShoe(); // This interaction allows the player to change the horse’s shoes and is dependent on the horseShoe_lvl value. 
void giveSnack(); // This interaction allows the player to feed the horse a snack and can decrease their hunger level slightly.  
void nextHour(int hours) override; // Updates the horse’s state over time, with boredom, sociability, and happiness decreasing more quickly than other pets. 

virtual bool save_file(const string &fileName) const override; // checks whether a file was able to successfully save the pet's state to a file or not. 
virtual bool load_file(const string &fileName) override; // checks whether a file was able to successfully load the pet's state from a file or not. 
bool delete_file(const string &fileName) override; 

void DisplayStats() override; // Displays all stats, including both inherited and horse-specific variables.     
void PrintOptions(bool &isPlaying) override; // Displays possible interaction options for the player to pick from.     
void doAction(int option,bool &isPlaying) override; // Accepts input from the user and does the action(s) associated with the option(s) selected. 
virtual ~Horse() override {};
};
