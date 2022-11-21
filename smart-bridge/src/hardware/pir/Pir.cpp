#include "Pir.h"
#include "Arduino.h"


Pir::Pir(int pin){
    this->pin = pin;
    this->calibrate();
}

void Pir::calibrate(){
    //Serial.println("Pir calibration : START");
    for(int i = 0; i < CALIBRATION_TIME_SEC; i++){
        //Serial.print(".");
        delay(1000);
    }
    //Serial.println();
    //Serial.println("Pir calibration : END");
}

int Pir::readValue(){
    return digitalRead(this->pin);
}

int Pir::getPin(){
    return this->pin;
}