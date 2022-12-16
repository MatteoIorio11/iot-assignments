#ifndef __JSONSERIALIZER__
#define __JSONSERIALIZER__

#include <Arduino.h>
#include "SoftwareSerial.h"

class Bluetooth{
    private:
        int TXpin;
        int Rxpin;
    public:
        Bluetooth(int RXpin, int TXpin);
        void init();
        void write(String val);
        String read();
};

#endif