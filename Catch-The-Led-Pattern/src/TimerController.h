#ifndef TIMER_CONTROLLER_H
#define TIMER_CONTROLLER_H
#define NOT_SET -1

using namespace std;

class TimerController{
    private :
        float timer_t1 = NOT_SET;
        float timer_t2 = NOT_SET;
        float timer_t3 = NOT_SET;
        float factor = 0;
        int offset = 5;
        int difficulty = 0;
    
    public:
        void selectDifficulty(int input);
        void ledsOff();
        void showPattern();
        void beginGame();
        int difficultySelected();
        void reduceTimers();
        void resetTimers();
        float getTimer1();
        float getTimer2();
        float getTimer3();
};

#endif