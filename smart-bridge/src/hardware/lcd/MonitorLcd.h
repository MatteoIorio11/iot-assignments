#ifndef __MONITORLCD__
#define __MONITORLCD__

#include <LiquidCrystal_I2C.h>
#include "State.h"
#define FIRST_ROW 0
#define SECOND_ROW 1
#define THIRD_ROW 2
#define FIRST_COL 0


class MonitorLcd{
    private:
        MonitorState state;
        LiquidCrystal_I2C* lcd;
        int address;
        int rows;
        int cols;
    public:
        MonitorLcd(int address, int rows, int cols);
        void init();
        void displayPreAlarm(double level);
        void displayAlarm(double level, int op_degree);
        void displayON();
        void displayOFF();
        MonitorState getState();
};

#endif