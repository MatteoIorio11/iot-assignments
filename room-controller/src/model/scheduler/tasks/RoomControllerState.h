#ifndef __RCSTATUS__
#define __RCSTATUS__

enum RoomControllerState{
    RUNNING = 0,
    WAITING_FOR_OPENING = 1,
    WAITING_FOR_CLOSING = 2
};

#endif