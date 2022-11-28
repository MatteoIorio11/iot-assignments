#ifndef __LOGICSLS__
#define __LOGICSLS__

#include "functionalities/smart-light-system/SmartLightSystem.h"
#include "functionalities/json/json-serialization/JsonSerializer.h"

void initSLS(int pin_pir, int pin_led, int pin_photo, int per);
void tickSLS(float p);
void setAlarm();
void resetStatus();
bool isInAlarmState();
bool detected();
SmartLightSystem* getSLS();

#endif