#include "Sonar.h"
#include "Arduino.h"


Sonar::Sonar(int trigPin, int echoPin){
    this->trigPin = trigPin;
    this->pin = echoPin;
}

void Sonar::sendImpulse(){
    digitalWrite(this->trigPin, LOW);
    delayMicroseconds(3);
    digitalWrite(trigPin, HIGH);   
    delayMicroseconds(5);
    digitalWrite(trigPin, LOW);
}

int Sonar::readValue(){
    this->sendImpulse();
    float tUS = pulseIn(this->pin, HIGH);
    float t = tUS / 1000.0 / 1000.0 / 2;
    float d = t * VS;
    return d;
}

int Sonar::getEchoPin(){
    return this->pin;
}

int Sonar::getTrigPin(){
    return this->trigPin;
}