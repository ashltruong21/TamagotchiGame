#pragma once
#include "Pet.h"
#include <iostream>

class Bird : public Pet {
protected:
    int flight_lvl; // to store the bird's flight level, reflects how willing the bird is to fly.     
public:
    Bird();

    void Feed() override; // decreases the hunger status, but if done repeatedly/when it’s full, it will not change the hunger status & decrease the happiness level. 
    void Rest() override; // decreases the sleepiness status, cannot be chosen if it’s fully rested. It may also automatically go to sleep if it’s too tired to do anything.  
    void Cuddle() override; // decreases how bored the pet is and increases happiness + sociability statuses.  
    void Observe() override; // generally decreases how bored the pet is until a certain point is hit (and decreases sociability level). 
    void CleanUp() override;

    void fly(); // Interaction where the bird flies around, decreasing flight_lvl & boredom while increasing other values. 
    void puzzleSolve(); // Interaction where the bird solves a puzzle, increasing/decreasing values based on the puzzle-solving experience.  
    void hideAndSeek(); // The player must find the bird. Success increases happiness and sociability, while failure may lower happiness + other values.    
    void MatchingGame(); // A memory matching game where the player matches cards. If successful with fewer mistakes, it increases happiness and stimulation.   
    void sing(); // The bird sings which increases happiness and sociability, if stimulation is high enough. 
    
    void nextHour(int Hours) override; // Updates the bird’s state over time, with hunger and boredom decreasing the fastest.    
    
    virtual bool save_file(const string &fileName) const override; // checks whether a file was able to successfully save the pet's state to a file or not. 
    virtual bool load_file(const string &fileName) override; // checks whether a file was able to successfully load the pet's state from a file or not. 
    bool delete_file(const string &fileName) override; 

    void DisplayStats() override; // Displays all stats, including both inherited and horse-specific variables.     
    void PrintOptions(bool &isPlaying) override; // Displays possible interaction options for the player to pick from.     
    void doAction(int option,bool &isPlaying) override; // Accepts input from the user and does the action(s) associated with the option(s) selected.    
    void printInstructions(); 
    virtual ~Bird() override {} // virtual bird destructor. 
};
