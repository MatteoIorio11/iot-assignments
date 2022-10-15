#include <Arduino.h>
#include <time.h>
#include "TimerController.h"

#define EASY 1
#define NORMAL 0.8
#define MEDIUM 0.6
#define HARD 0.4
#define NOT_SET -1
using namespace std;

void TimerController::selectDifficulty(int input){
    this->difficulty = map(input, 0, 1023, 1, 5);
    switch (this->difficulty)
    {
        case 1:
            this->factor = EASY; 
            break;
        case 2:
            this->factor = NORMAL;
            break;
        case 3:
            this->factor = MEDIUM;
            break;
        case 4:
            this->factor = HARD;
            break;
    }
}
void TimerController::ledsOff(){
    randomSeed(analogRead(1));
    // manage the timer t1 : the leds L1…L4 are turned off for some random time T1 
    this->timer_t1 = random(5,10);
}
void TimerController::showPattern(){
    
    //manage the timer t2 : the leds are then turned on according to some  random pattern, for some time T2 and then turned off again 
    if(this->timer_t2 == NOT_SET){
        randomSeed(analogRead(1));
        this->timer_t2 =  random(5,10);
    }
}
void TimerController::beginGame(){
    //manage the timer t3 : the player has max T3 time for recreating the pattern by pressing the buttons T1…T4 
    if(this->timer_t3 == NOT_SET){
        randomSeed(analogRead(1));
        this->timer_t3 =  random(5,10);
    }
}

int TimerController::difficultySelected(){
    randomSeed(analogRead(1));
    return this->difficulty;
}

void TimerController::reduceTimers(){
    this->timer_t2 = this->timer_t2*this->factor;
    this->timer_t3 = this->timer_t3*this->factor;
}

float TimerController::getTimer1(){
    return this->timer_t1;
}
float TimerController::getTimer2(){
    return this->timer_t2;
}
float TimerController::getTimer3(){
    return this->timer_t3;
}

void TimerController::resetTimers(){
    this->timer_t2 = NOT_SET;
    this->timer_t3 = NOT_SET;
}