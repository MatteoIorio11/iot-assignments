#include <Arduino.h>
#include <TimerOne.h>
#include <ArduinoJson.h>
#include "logic/timer/Timer.h"

#include "logic/timer/Timer.h"
#include "logic/logic-smart-light-system/LogicSLS.h"
#define PIN_LED 12
#define PIN_PIR 2
#define PIN_PHOTORESISTOR A0
#define PERIOD 100

Timer* t;

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
  t->changeState(); 
}


void setup() {
  Serial.begin(9600);
  t = new Timer();
  t->getTimer()->attachInterrupt(changeState);
}

void loop() {
  // put your main code here, to run repeatedly:
  t->waitForTheNextTick();
  //tickSLS();
  Serial.println("ESEGUO");
}