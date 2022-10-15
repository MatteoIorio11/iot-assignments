#include <Arduino.h>

#include "GreenLed.cpp"
#include "RedLed.cpp"
#include "Status.cpp"
#include "User.cpp"
#include "Bot.cpp"
#include "TimerController.cpp"

class GameController{
    private:
        STATUS status;
        User *user;
        Bot *bot;
        TimerController *timer;
        int penalties;
        int score;

    public:
        GameController(){
            user = new User();
            bot = new Bot();
            timer = new TimerController();
            penalties = 0;
            score = 0;
        }



        void phaseSelectLeds(){
            status = GAME_SCORE; 
        }

        void phaseWakeUp(){
            status = INPUT_WAIT;
        }

        void phaseGameScore(){
            status = GAME_SCORE;
        }

        void phaseRecreatePattern(){
            user->resetAllPositions();
            status = RECREATE_PATTERN;
        }

        void botGenerateSequence(){
            bot->generateSequence();
        }

        void phaseShowPattern(){
            status = SHOW_PATTERN;
        }

        void phasePenalty(){
            status = PENALTY;
        }

        void phaseStartGame(){
            status = GAME_START;
        }

        void selectDifficulty(int difficulty){
            timer->selectDifficulty(difficulty);
        }

        int getSelectedDifficulty(){
            return timer->difficultySelected();
        }

        void timerLedsOff(){
            timer->ledsOff();
        }

        void getTimerT1(){
            return timer->getTimer1();
        }

        bool checkSequence(bool* input){
            for(int i = 0; i < NLED; i++){
                if(bot->getSequence()[i] != input[i]){
                    return false;
                }
            }
            return true;
        }
        
        STATUS getStatus(){
            return status;
        }
        
        int getPenalties(){
            return penalties; 
        }
        
        int getScore(){
            
        }
}