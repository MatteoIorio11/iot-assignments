#include "Pir.h"
#include "Arduino.h"

#define CALIBRATION_TIME_SEC 10
#define DETECTED 1
#define NOT_DETECTED 0

Pir::Pir(int pin){
    this->pin = pin;
    this->calibrate();
}

void Pir::calibrate(){
    for(int i = 0; i < CALIBRATION_TIME_SEC; i++){
    delay(1000);
  }
}

int Pir::readValue(){
    int value = digitalRead(this->pin);
    return value == HIGH ? DETECTED : NOT_DETECTED;
}