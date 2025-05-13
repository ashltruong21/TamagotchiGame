#pragma once
#include <iostream>
#include "Pet.h" 

class Cat : public Pet {
protected: 
int scratch_lvl; // to store the level indicating how much the cat wants to scratch something. 

public:
Cat(); // default constructor that sets type to “Cat”, scratch level to 50, and sociability to 25 and the remaining variables to their default values in the Pet default constructor. 

void Feed() override; // decreases the hunger status, but if done repeatedly/when it’s full, it will not change the hunger status & decrease the happiness level. 
void Rest() override; // decreases the sleepiness status, cannot be chosen if it’s fully rested. It may also automatically go to sleep if it’s too tired to do anything.  
void Cuddle() override; // decreases how bored the pet is and increases happiness + sociability statuses.  
void Observe() override; // generally decreases how bored the pet is until a certain point is hit (and decreases sociability level). 
void CleanUp() override; 

void scratchPost(); // This interaction changes values to represent it when the cat is allowed to scratch a post. 
void chaseLaser(); // This interaction increases/decreases values to reflect a cat playing with a laser.  
void catJungle(); // This interaction increases/decreases values to reflect a cat climbing & playing on a cat jungle gym. 
void takeNap(); // Interaction where the cat takes a nap, reducing sleepiness and slightly increasing happiness and sociability. 
void walk(); // This interaction increases/decreases values to show a cat taking a walk with their owner.  

void nextHour(int hours) override; // Updates the cat’s state over time with various changes in values. More notably their sleepiness & happiness changes faster than other pets.  

bool save_file(const string &fileName) const override; // Saves the cat's state to a file. 
bool load_file(const string &fileName) override; // Loads the cat's state from a file. 
bool delete_file(const string &fileName) override; 

void DisplayStats() override; // Displays all stats, including both inherited and cat-specific variables.      
void PrintOptions(bool &isPlaying) override; // Displays possible interaction options for the player to pick from.      
void doAction(int option,bool &isPlaying) override; // Accepts input from the user and does the action(s) associated with the option(s) selected.  

virtual ~Cat() override {}; // virtual cat destructor.
};