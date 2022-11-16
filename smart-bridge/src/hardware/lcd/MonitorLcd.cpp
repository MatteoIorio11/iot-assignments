#include "MonitorLcd.h"
#include <LiquidCrystal_I2C.h>
#include "Arduino.h"

#define STRING_PRE_ALARM " PRE-ALARM "
#define STRING_ALARM " ALARM "
#define WATER_LEVEL(l) ("Water Level (cm): "+l)
#define OPENING_DEGREE(d) ("Opening degree:"+d)

MonitorLcd::MonitorLcd(int address, int rows, int cols){
    this->state = MONITOR_OFF;
    this->address = address;
    this->rows = rows;
    this->cols = cols;
}

void MonitorLcd::init(){
    this->lcd = new LiquidCrystal_I2C(0x27, this->rows, this->cols); 
    this->lcd->init();

}

void MonitorLcd::displayON(){
    this->lcd->backlight();
    this->state = MONITOR_ON;
}

void MonitorLcd::displayOFF(){
    this->lcd->noBacklight();
    this->state = MONITOR_OFF;
}

//The LCD is turned on, informing about the pre-alarm and displaying the current water level
void MonitorLcd::displayPreAlarm(double level){
    this->lcd->clear();
    this->lcd->setCursor(1,1);
    this->lcd->print(STRING_PRE_ALARM);  
    if(this->rows > 1){
        this->lcd->setCursor(2,1);
        this->lcd->print(String(level));
    }
    
}

//The LCD is still on, informing about the alarm situation and displaying both the current water level and the opening degrees of the valve 
void MonitorLcd::displayAlarm(double level, int op_degree){
    
    this->lcd->clear();
    this->lcd->setCursor(1,1);
    this->lcd->print(STRING_ALARM);
    if(this->rows > 2){
        this->lcd->setCursor(2,1);
        this->lcd->print(WATER_LEVEL(String(level)));
        this->lcd->setCursor(3,1);
        this->lcd->print(OPENING_DEGREE(String(op_degree)));
    }
    
}

MonitorState MonitorLcd::getState(){
    return this->state;
}