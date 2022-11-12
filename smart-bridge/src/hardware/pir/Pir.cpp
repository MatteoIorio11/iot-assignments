#include "Pir.h"
#include "Arduino.h"

#define CALIBRATION_TIME_SEC 10

Pir::Pir(int pin){
    this->pin = pin;
    this->calibrate();
}

void Pir::calibrate(){
    Serial.println("Pir calibration : START");
    for(int i = 0; i < CALIBRATION_TIME_SEC; i++){
    delay(1000);
    }
    Serial.println("Pir calibration : END");
}

int Pir::readValue(){
    return digitalRead(this->pin);
}

int Pir::getPin(){
    return this->pin;
}