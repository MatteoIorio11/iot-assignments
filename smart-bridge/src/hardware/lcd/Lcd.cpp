#include "LiquidCrystal_I2C.h"
#include "Lcd.h"


Lcd::Lcd(int address, int rows, int cols){
    this->address = address;
    this->rows = rows;
    this->cols = cols;
    this->lcd = LiquidCrystal_I2C(address, rows, cols); 
}

Lcd::displayPreAlarm(){

}