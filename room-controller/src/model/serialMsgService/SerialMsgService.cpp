
#include "Arduino.h"
#include "SerialMsgService.h"

String content;
SerialMsgService MsgService;

bool SerialMsgService::isMsgAvailable(){
  this->serialEvent();
  return msgAvailable;
}

Msg* SerialMsgService::receiveMsg(){
  if (msgAvailable){
    Msg* msg = currentMsg;
    msgAvailable = false;
    currentMsg = NULL;
    content = "";
    return msg;  
  } else {
    return NULL; 
  }
}

void SerialMsgService::init(){
  Serial.begin(9600);
  content.reserve(256);
  content = "";
  currentMsg = NULL;
  msgAvailable = false;  
}

void SerialMsgService::sendMsg(const String& msg){
  Serial.println(msg);  
}

void SerialMsgService::serialEvent() {
  /* reading the content */
  while (Serial.available()) {
      content = Serial.readString();
      MsgService.currentMsg = new Msg(content);
      MsgService.msgAvailable = true;   
      Serial.println("AA");  
  }
}