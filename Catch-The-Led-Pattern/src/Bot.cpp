#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<Arduino.h>




#define NLED 4

class Bot{
    private:
        int positions[NLED] = {0, 0, 0, 0};

    public:

        /*  builds the light pattern
        *
        */

        void generateSequence(){
            int count = 1;
            srand((unsigned) time(NULL));
            while(count <= 4){
                int randNum = rand() % 4;
                while(this->positions[randNum] != 0){
                    randNum = rand() % 4;
                }
                this->positions[randNum] = count;
                count++;
            }
        }

        /*
        *   returns the sequence
        */

        int* getSequence(){
            return this->positions;
        }

        /*
        *   Validates the choice
        */


        bool validate(int position, int val){
            if(this->positions[position] == val){
                return true;
            }else{
                return false;
            }
        }

        /*
        *   Resets the sequence
        */

        void resetSequence(){
            for(int i = 0; i < 3; i++){
                this->positions[i] = 0;
            }
        }
};
