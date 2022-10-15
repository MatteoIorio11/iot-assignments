#ifndef USER_H
#define USER_H
#define NLED 4
using namespace std;

class User{
    private :
        //GreenLed positionLed[NLED]; 
        bool positions[NLED] = {false};    
    public :
        void addPos(int selected_pos);
        void resetAllPositions();
        bool* getPositions();
};
#endif