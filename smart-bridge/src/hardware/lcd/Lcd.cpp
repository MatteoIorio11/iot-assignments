#include "LiquidCrystal_I2C.h"
#include "Lcd.h"

#define STRING_PRE_ALARM "This is the pre-alarm alert, please be carefull"
#define WATER_LEVEL(l) ("Water Level (cm): "+(l))

Lcd::Lcd(int address, int rows, int cols){
    this->address = address;
    this->rows = rows;
    this->cols = cols;
    this->lcd = LiquidCrystal_I2C(address, rows, cols); 
    this->lcd.init();
}

void Lcd::displayON(){
    this->lcd.backlight();
}

void Lcd::displayOFF(){
    this->lcd.noBacklight();
}

//The LCD is turned on, informing about the pre-alarm and displaying the current water level
void Lcd::displayPreAlarm(double level){
    this->lcd.setCursor(1,1);
    this->lcd.print(STRING_PRE_ALARM);
    this->lcd.setCursor(3,1);
    this->lcd.print(WATER_LEVEL(level));
}