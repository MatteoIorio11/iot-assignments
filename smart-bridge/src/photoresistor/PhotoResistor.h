#ifndef __PHOTORESISTOR__
#define __PHOTORESISTOR__

#include "task/Task.h"

class PhotoResistor : public Task{
    private:
        int pin;
    public:
        PhotoResistor(int pin);
        int readValue();
};

#endif