#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<Arduino.h>




#define NLED 4

class Bot{
    private:
        bool positions[NLED] = {false};

    public:

        /*  builds the light pattern
        *
        */

        void generateSequence(){
            int count = 1;
            srand((unsigned) time(NULL));
            for(int i = 0; i < NLED; i++){
                //If the random number generated is even, then the led is setted to TRUE ( LIGHT ON ), in the other case the led is off.
                this->positions[i] = ((rand() % 10) + 1) % 2 == 0 ? true : false;
            }
        }

        /*
        *   returns the sequence
        */

        bool* getSequence(){
            return this->positions;
        }

        /*
        *   Validates the choice
        */


        bool validate(int position, int val){
            return this->positions[position] == val;
        }

        /*
        *   Resets the sequence
        */

        void resetSequence(){
            for(int i = 0; i < NLED; i++){
                this->positions[i] = false;
            }
        }
};
