#ifndef __LOGICWCS__
#define __LOGICWCS__

void initWCS(int pin_servo, int pin_pot, int pin_button, int sonar_echoPin, int sonar_trigPin, int red_pin_led, int green_pin_led);
void tickWCS();
void automatic();
void buttonHandler();

#endif