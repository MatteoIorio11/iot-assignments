#include <Arduino.h>
#include <TimerOne.h>
#include <ArduinoJson.h>
#include "bridge/Bridge.h"
#include "hardware/servomotor/ServoMotor.h"
Bridge* b;
ServoMotor *s;

void changeTheState(){
  b->getTimer()->changeState();
}

void setup()
{
  Serial.begin(9600);
  b = new Bridge();
  b->init();
  b->getTimer()->getTimerOne()->attachInterrupt(changeTheState); 
}


void loop() {
  /*
  for(int i = 0; i < 180; i++){
    s->setAngle(i);
    delay(10);
  }
  delay(2000);
  s->setAngle(0);
  delay(2000);
  */
  // put your main code here, to run repeatedly:
  b->getTimer()->waitForTheNextTick();
  b->tick();
  //JsonSerializer::serialize(NORMAL, 10.0, 1);
  delay(1000);
}