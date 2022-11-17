#ifndef __LOGICSLS__
#define __LOGICSLS__

#include "functionalities/smart-light-system/SmartLightSystem.h"

void initSLS(int pin_pir, int pin_led, int pin_photo, int per);
void tickSLS(float p);
void setAlarm();
void changePeriod(long p);//Period of the Timer
bool isInAlarmState();
SmartLightSystem* getSLS();

#endif