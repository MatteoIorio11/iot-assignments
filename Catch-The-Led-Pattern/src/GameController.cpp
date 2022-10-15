#include <Arduino.h>

#include "Status.h"
#include "User.h"
#include "Bot.h"
#include "TimerController.h"

using namespace std;

class GameController{
    private:
        STATUS status;
        User user;
        Bot bot;
        TimerController timer;
        int penalties;
        int score;

    public:
        GameController(){
            this->status = INPUT_WAIT;
            this->penalties = 0;
            this->score = 0;
        }

        void phaseDeepSleep(){
            this->status = DEEP_SLEEP;
        }

        void phaseSelectLeds(){
            this->status = GAME_SCORE; 
        }

        void phaseWakeUp(){
            this->status = INPUT_WAIT;
        }

        void phaseGameScore(){
            this->status = GAME_SCORE;
        }

        void phaseRecreatePattern(){
            this->user.resetAllPositions();
            this->status = RECREATE_PATTERN;
        }

        void botGenerateSequence(){
            this->bot.generateSequence();
        }

        void phaseShowPattern(){
            this->status = SHOW_PATTERN;
        }

        void phasePenalty(){
            this->status = PENALTY;
        }

        void phaseStartGame(){
            this->status = GAME_START;
        }

        void phaseGameOver(){
            this->status = GAME_OVER;
        }


        void selectDifficulty(int difficulty){
            this->timer.selectDifficulty(difficulty);
        }

        int getSelectedDifficulty(){
            return this->timer.difficultySelected();
        }

        void timerLedsOff(){
            this->timer.ledsOff();
        }

        void timerShowPattern(){
            this->timer.showPattern();
        }

        void timerBeginGame(){
            this->timer.beginGame();
        }

        float getTimerT1(){
            return this->timer.getTimer1();
        }

        float getTimerT2(){
            return this->timer.getTimer2();
        }

        float getTimerT3(){
            return this->timer.getTimer3();
        }

        void timerReduceTimers(){
            this->timer.reduceTimers();
        }

        bool* getBotLeds(){
            return this->bot.getLeds();
        }

        bool* getUserLeds(){
            return this->user.getPositions();
        }

        void userResetAllPositions(){
            this->user.resetAllPositions();
        }

        void userAddPosition(int position){
            this->user.addPos(position);
        }

        bool checkSequence(){
            for(int i = 0; i < NLED; i++){
                if(this->user.getPositions()[i] != this->bot.getLeds()[i]){
                    return false;
                }
            }
            return true;
        }
        
        STATUS getStatus(){
            return this->status;
        }
        
        void addPenalty(){
            this->penalties++;
        }
        void increaseScore(){
            this->score++;
        }

        bool isGameOver(){
            return this->penalties >= 3; 
        }
        
        int getScore(){
            return this->score;
        }

        void resetGame(){
            this->score = 0;
            this->penalties = 0;
            this->timer.resetTimers();
            this->timer.showPattern();
            this->timer.beginGame();
        }
};