#ifndef __PIR__
#define __PIR__

class Pir{
    private:
        int pin;
    public:
        Pir(int pin);
        void calibrate();
        int readValue();
};

#endif