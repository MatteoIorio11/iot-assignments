#include "Sonar.h"
#include "Arduino.h"


Sonar::Sonar(int trigPin, int echoPin){
    this->trigPin = trigPin;
    this->echoPin = echoPin;
}

void Sonar::sendImpulse(){
    digitalWrite(this->trigPin, LOW);
    delayMicroseconds(3);
    digitalWrite(trigPin, HIGH);   
    delayMicroseconds(5);
    digitalWrite(trigPin, LOW);
}

int Sonar::getDistance(){
    this->sendImpulse();
    float tUS = pulseIn(this->echoPin, HIGH);
    float t = tUS / 1000.0 / 1000.0 / 2;
    float d = t * VS;
    return d;
}