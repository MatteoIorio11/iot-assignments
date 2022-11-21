#ifndef __LOGICWCS__
#define __LOGICWCS__
#include "logic/timer/Timer.h"
#include "functionalities/json/json-serialization/JsonSerializer.h"
#include "contants/Constants.h"

void initWCS(Timer* t, int pin_servo, int pin_pot, int pin_button, int sonar_echoPin, int sonar_trigPin, int red_pin_led, int green_pin_led, int address, int rows, int cols);
void tickWCS();
void automatic();
void buttonHandler();

#endif