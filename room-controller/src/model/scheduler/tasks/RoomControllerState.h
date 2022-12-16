#ifndef __RCSTATUS__
#define __RCSTATUS__

enum RoomControllerState{
    RUNNING = 0,
    WAITING_FOR_OPENING = 1,
    WAITING_FOR_CLOSING = 2,
    OPENING_ROLLER_BLINDS = 3,
    CLOSING_ROLLER_BLINDS = 4,
    SETTING_LED_OFF = 5,
    SETTING_LED_ON = 6

};

#endif