#ifndef __SERIALMSGSERVICE__
#define __SERIALMSGSERVICE__

#include "Arduino.h"
#include "model/msg/Msg.h"

class SerialMsgService {
    public: 
        Msg* currentMsg;
        bool msgAvailable;
        void init();  
        bool isMsgAvailable();
        Msg* receiveMsg();  
        void sendMsg(const String& msg);
};
extern SerialMsgService MsgService;
#endif