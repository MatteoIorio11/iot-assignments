#ifndef __BLUETOOTH__
#define __BLUETOOTH__

#include <Arduino.h>
#include "SoftwareSerial.h"
#include "Msg.h"

class Bluetooth{
    private:
        int TXpin;
        int RXpin;
        Msg* availableMsg;
        SoftwareSerial* btChannel;
    public:
        Bluetooth(int RXpin, int TXpin);
        void init();
        void write(Msg val);
        bool isMsgAvailable();
        Msg* read();
};

#endif