#include "LiquidCrystal_I2C.h"
#include "Lcd.h"

#define STRING_PRE_ALARM "!!PRE-ALARM!!"
#define STRING_ALARM "!!ALARM!!"
#define WATER_LEVEL(l) ("Water Level (cm): "+(l))
#define OPENING_DEGREE(d) ("Opening degree:"+(d))

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
    this->lcd.clear();
    this->lcd.setCursor(1,1);
    this->lcd.print(STRING_PRE_ALARM);
    if(this->rows > 1){
        this->lcd.setCursor(2,1);
        this->lcd.print(WATER_LEVEL(level));
    }
}

//The LCD is still on, informing about the alarm situation and displaying both the current water level and the opening degrees of the valve 
void Lcd::displayAlarm(double level, int op_degree){
    this->lcd.clear();
    this->lcd.setCursor(1,1);
    this->lcd.print(STRING_PRE_ALARM);
    if(this->rows > 2){
        this->lcd.setCursor(2,1);
        this->lcd.print(WATER_LEVEL(level));
        this->lcd.setCursor(3,1);
        this->lcd.print(OPENING_DEGREE(op_degree));
    }
}