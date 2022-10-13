#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<Arduino.h>


#define NLED 4

class Bot{
    private:
        bool leds[NLED] = {false};
        
    public:
        /*  builds the light pattern
        * 
        */

        void generateSequence(){
            randomSeed(analogRead(1));
            for(int i = 0; i < NLED; i++){
                //srand(time(NULL));
                //If the random number generated is even, then the led will be setted to TRUE ( LIGHT ON ), in the other case the led is off.
                this->leds[i] = (random()) % 2 == 0;
            }
        }

        /*
        *   returns the sequence
        */

        bool* getLeds(){
            return this->leds;
        }

        /*
        *   Validates the choice
        */


        bool validate(int position, bool val){
            return this->leds[position] == val;
        }

        bool validate(bool* input_array){
            for(int i = 0; i < NLED; i++){
                if(this->leds[i] != input_array[i]){
                    return false;
                }
            }
            return true;
        }

        /*
        *   Resets the sequence
        */

        void allLedsOff(){
            for(int i = 0; i < NLED; i++){
                this->leds[i] = false;
            }
        }
};
