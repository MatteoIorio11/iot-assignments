#include <Arduino.h>
#include <TimerOne.h>
#include <library.json>

#include "logic/logic-smart-light-system/LogicSLS.h"
#define PIN_LED 12
#define PIN_PIR 2
#define PIN_PHOTORESISTOR A0
#define PERIOD 100

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


void setup() {
  Serial.begin(9600);
  //initSLS(PIN_PIR, PIN_LED, PIN_PHOTORESISTOR, PERIOD);
  state = OFF;
  /*
  if(PERIOD > 0){
    timer.setupPeriod(PERIOD);
  }else{
    timer.setupPeriod(100);
  }
  */
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
  //timer.waitForNextTick();
  //tickSLS();
}