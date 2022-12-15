#include "hardware/pir/Pir.h"

/// @brief Constructor
/// @param pin digital pin of the pir
Pir::Pir(int pin){
    this->pin = pin;
    this->calibrate();
}

/// @brief Calibration of the Sensor
void Pir::calibrate(){
    for(int i = 0; i < CALIBRATION_TIME_SEC; i++){
        delay(1000);
    }
}

/// @brief Understand if someone is detected from the pir
/// @return The value read from the Pir
int Pir::readValue(){
    return digitalRead(this->pin);
}

/// @brief Understand which pin the Pir use
/// @return The Pir's pin
int Pir::getPin(){
    return this->pin;
}