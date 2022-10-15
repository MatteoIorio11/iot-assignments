#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<Arduino.h>
#include "Bot.h"

#define NLEDS 4
using namespace std;

void Bot::generateSequence(){
    randomSeed(analogRead(1));
    for(int i = 0; i < NLEDS; i++){
        //srand(time(NULL));
        //If the random number generated is even, then the led will be setted to TRUE ( LIGHT ON ), in the other case the led is off.
        this->leds[i] = (random()) % 2 == 0;
    }
}

/*
*   returns the sequence
*/

bool* Bot::getLeds(){
    return this->leds;
}
/*
*   Validates the choice
*/


bool Bot::validate(int position, bool val){
    return this->leds[position] == val;
}

bool Bot::validate(bool* input_array){
    for(int i = 0; i < NLEDS; i++){
        if(this->leds[i] != input_array[i]){
            return false;
        }
    }
    return true;
}
/*
*   Resets the sequence
*/

void Bot::allLedsOff(){
    for(int i = 0; i < NLEDS; i++){
        this->leds[i] = false;
    }
};
