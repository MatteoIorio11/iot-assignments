#include <Arduino.h>
#include <TimerOne.h>
#include <ArduinoJson.h>
#include "bridge/Bridge.h"
Bridge* b;

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
  b->getTimer()->waitForTheNextTick();
  b->tick();
}