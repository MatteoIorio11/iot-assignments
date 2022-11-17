#include <Arduino.h>
#include <TimerOne.h>
#include <ArduinoJson.h>
#include "bridge/Bridge.h"
#include "functionalities/json/json-serialization/JsonSerializer.h"
#include "functionalities/waterflow-control-system/State.h"
#include "hardware/servomotor/ServoMotor.h"

Bridge* b;
ServoTimer2* s;
void changeTheState(){
  b->getTimer()->changeState();
}

void setup()
{
  Serial.begin(9600);
  //b = new Bridge();
  //b->init();
  //b->getTimer()->getTimerOne()->attachInterrupt(changeTheState); 
  s = new ServoTimer2();
  s->attach(A1);

}


void loop() {
  // put your main code here, to run repeatedly:
  //b->getTimer()->waitForTheNextTick();
  //b->tick();
}