#ifndef __HARDWARE__
#define __HARDWARE__

class Hardware{
    private:
        int pin;
    public:
        int getPin();
        int readValue();
};

#endif