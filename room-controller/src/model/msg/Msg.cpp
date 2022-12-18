#include "Msg.h"

Msg::Msg(const String& content){
    this->content = content;
}
  
String Msg::getContent(){
    return this->content;
}