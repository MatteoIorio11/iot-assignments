#include <Arduino.h>
#include <TimerOne.h>
#include <ArduinoJson.h>
#include "bridge/Bridge.h"
#define PIN_LED 12
#define PIN_PIR 2
#define PIN_PHOTORESISTOR A0
#define PERIOD 100

Bridge* b;

/*
void setup() {
 Serial.begin(115200);
 Serial.setTimeout(1);
}
void loop() {
 while (!Serial.available());
 x = Serial.readString().toInt();
 Serial.print(x + 1);
}

{ 
  "degree":"X",
  "message":"myMessage",
  "":
}

A.setMessage("aaaaa")
A.parse(); ==> {degree="VALORE_LETTO_INPUT", message"aaaaa", ...}



*/

void changeState(){
  b->getTimer()->changeState();
}


void setup() {
  Serial.begin(9600);
  b = new Bridge();
  b->getTimer()->getTimerOne()->attachInterrupt(changeState);
}

void loop() {
  // put your main code here, to run repeatedly:
  b->getTimer()->waitForTheNextTick();
  b->tick();
  //tickSLS();
}