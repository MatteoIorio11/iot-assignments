#include "Bridge.h"

Bridge::Bridge(){
    this->timer = new Timer();
}

void Bridge::init(){
    //initSLS(this->timer);
    //initWCS(this->timer);
}

Timer* Bridge::getTimer(){
    return this->timer;
}

void Bridge::tick(){
    tickWCS();
}

