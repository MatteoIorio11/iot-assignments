#include "Sonar.h"
#include "Arduino.h"

const double VS =  331.45 + 0.62*20;

Sonar::Sonar(int trigPin, int echoPin){
    this->trigPin = trigPin;
    this->pin = echoPin;
    pinMode(this->trigPin, OUTPUT);
    pinMode(this->pin, INPUT);  
}

void Sonar::sendImpulse(){
    digitalWrite(this->trigPin, LOW);
    delayMicroseconds(3);
    digitalWrite(this->trigPin, HIGH);   
    delayMicroseconds(5);
    digitalWrite(this->trigPin, LOW);
}

float Sonar::readValue(){    
    this->sendImpulse();
    long tUS = pulseInLong(this->pin, HIGH);

    double t = tUS / 1000.0 / 1000.0 / 2;
    double d = t*VS;
    return d;
}
    
int Sonar::getEchoPin(){
    return this->pin;
}

int Sonar::getTrigPin(){
    return this->trigPin;
}