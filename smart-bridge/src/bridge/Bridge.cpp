#include "Bridge.h"

Bridge::Bridge(){
    this->timer = new Timer();
}

void Bridge::init(){
    initSLS(PIN_PIR, PIN_LED, PIN_PHOTORESISTOR, NORMAL_STATE_SAMPLING);
    initWCS(this->timer, );
}

Timer* Bridge::getTimer(){
    return this->timer;
}

void Bridge::tick(){
    tickWCS();
}

