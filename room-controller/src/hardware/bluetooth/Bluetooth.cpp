#include "Bluetooth.h"
/// @brief Constructor for the bluetooth sensor
/// @param RXpin 
/// @param TXpin 
Bluetooth::Bluetooth(int RXpin, int TXpin){
    this->RXpin = RXpin;
    this->TXpin = TXpin;
    this->init();
}

/// @brief initializing the component
void Bluetooth::init(){
    this->btChannel = new SoftwareSerial(this->RXpin, this->TXpin);
    btChannel->begin(2400);
}

/// @brief tells if the message is advaiable
/// @return true if there's any message false otherwise
bool Bluetooth::isMsgAvailable(){
    String content = "";
    while (btChannel->available()) {
        content= btChannel->readString();
        this->availableMsg = new Msg(content); 
        content = "";
        return true;    
    }
    return false;  
}

/// @brief reading from the bluetooth
/// @return the read value
Msg* Bluetooth::read(){
    if (availableMsg != NULL){
        Msg* msg = availableMsg;
        availableMsg = NULL;
        return msg;  
    } else {
        return NULL;
    }
}

/// @brief writes the passed message on the bluetooth channel
/// @param val 
void Bluetooth::write(Msg val){
    btChannel->println(val.getContent());  
}