#ifndef __LCD__
#define __LCD__

#include "LiquidCrystal_I2C.h"

class Lcd{
    private:
        LiquidCrystal_I2C lcd;
        int address;
        int rows;
        int cols;
    public:
        Lcd(int address, int rows, int cols);
        void displayPreAlarm(double level);
        void displayAlarm();
        void displayON();
        void displayOFF();
};

#endif