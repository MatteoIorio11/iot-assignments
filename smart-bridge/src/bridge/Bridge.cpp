#include "Bridge.h"

Bridge::Bridge(){
    this->timer = new Timer();
}

void Bridge::Synchronize(){
    while(!Serial.available()){}
    //This method is used in order to synchronize the PC to the Arduino because we do not want to lose messages
}

void Bridge::init(){
    this->Synchronize();
    //initWCS(this->timer, PIN_SERVO_MOTOR,PIN_POTENTIOMETER,PIN_BUTTON, PIN_SONAR, PIN_SONAR_TRG, PIN_REDLED_WCS, PIN_GREENLED_WCS, MONITOR_ADDRESS, ROWS, COLS);
    //initSLS(PIN_PIR, PIN_LED_SLS, PIN_PHOTORESISTOR, NORMAL_STATE_SAMPLING);
}

Timer* Bridge::getTimer(){
    return this->timer;
}

void Bridge::tick(){
    tickWCS();
}

