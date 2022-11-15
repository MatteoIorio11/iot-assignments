#ifndef __LOGICSLS__
#define __LOGICSLS__


void initSLS(int pin_pir, int pin_led, int pin_photo, int per);
void tickSLS();
void setAlarm();
void changePeriod(long p);//Period of the Timer

#endif