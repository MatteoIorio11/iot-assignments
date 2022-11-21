#include "Sonar.h"
#include "Arduino.h"


/// @brief speed used to calculate the distance
const double VS =  331.45 + 0.62*20;

Sonar::Sonar(int trigPin, int echoPin){
    this->trigPin = trigPin;
    this->pin = echoPin;
    pinMode(this->trigPin, OUTPUT);
    pinMode(this->pin, INPUT);  
}

/// @brief and receive an impulse
void Sonar::sendImpulse(){
    digitalWrite(this->trigPin, LOW);
    delayMicroseconds(3);
    digitalWrite(this->trigPin, HIGH);   
    delayMicroseconds(5);
    digitalWrite(this->trigPin, LOW);
}

/// @brief calculates the length of an impulse and return the distance between the sonar and the object
/// @return the distance between the sonar and the nearest object
float Sonar::readValue(){    
    this->sendImpulse();
    long tUS = pulseInLong(this->pin, HIGH);

    double t = tUS / 1000.0 / 1000.0 / 2;
    double d = t*VS;
    return d;
}

/// @return the echo pin
int Sonar::getEchoPin(){
    return this->pin;
}

/// @return the trigpin
int Sonar::getTrigPin(){
    return this->trigPin;
}