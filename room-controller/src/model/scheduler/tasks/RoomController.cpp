#include "RoomController.h"


/// @brief Constructor of the RoomController
/// @param pin_led Led's pin
/// @param pin_servo ServoMotor's pin
RoomController::RoomController(int pin_led, int pin_servo, int RX_pin, int TX_pin){
    this->pin_led = pin_led;
    this->pin_servo = pin_servo;
    this->RX_pin = RX_pin;
    this->TX_pin = TX_pin;
    this->state = RUNNING;
    this->init();
}

/// @brief Init of all the components
void RoomController::init(){
    this->attachLed();
    this->attachServo();
    this->btMsg = new DynamicJsonDocument(64);
    this->serialMsg = new DynamicJsonDocument(128);
    this->bluetooth = new Bluetooth(this->RX_pin, this->TX_pin);
    MsgService.init();
}

/// @brief Attach the led
void RoomController::attachLed(){
    this->led = new Led(this->pin_led);
}

/// @brief Attach the servo
void RoomController::attachServo(){
    this->servo = new ServoMotor(this->pin_servo);
}


/// @brief used to read the new messages from the dashboard
/// @return true if the message was advailable false otherwise
bool RoomController::readSerialMessage(){
    if (MsgService.isMsgAvailable()) {
        Msg* msg = MsgService.receiveMsg();
        char ar [256];
        msg->getContent().toCharArray(ar, msg->getContent().length());
        deserializeJson(*this->serialMsg, ar); //deserializing of te JSON
        delete msg;
        return true;
    }else{
        return false;
    }
}


/// @brief used to read the new messages from android
/// @return true if the message was advailable false otherwise
bool RoomController::readBtMessage(){
    if(this->bluetooth->isMsgAvailable()){//checking if the android has sent any messages
        Msg* msg = this->bluetooth->read();  
        char ar [256];  
        msg->getContent().toCharArray(ar, msg->getContent().length());
        deserializeJson(*this->btMsg, ar); //deserializing of te JSON
        delete msg;
        return true;
    }else{
        return false;
    }
}
/// @brief it sets the led to ON
void RoomController::setLedON(){
    this->led->ledOn();
}
/// @brief it sets the led to OFF
void RoomController::setLedOFF(){
    this->led->ledOff();
}
/// @brief it sets the angle of the servo to the given one
/// @param angle 
void RoomController::setAngle(int angle){
    this->servo->setOpening(angle);
}

/// @brief State Machine of the RoomController
void RoomController::tick(){
    
    switch (this->state)
    {
        case RUNNING:
            //if we don't have any new message we don't do anything
            if(this->readSerialMessage())
            {
                String el = (*this->serialMsg)["hardware"];
                if(el =="LED"){
                    if((*this->serialMsg)["state"]){
                        this->setLedON();
                    }
                    //if switch to OFF
                    if(!(*this->serialMsg)["state"]){
                        this->setLedOFF();
                    }
                }else if(el == "SERVOMOTOR"){
                    this->setAngle((int)((*this->serialMsg)["angle"]));
                }else if(el == "PIR"){
                    if((*this->serialMsg)["lum"]){
                        this->setLedON();
                    }else{
                        this->setLedOFF();
                    }
                } else if(el == "TIME"){
                    //if time == 8.00
                    if((*this->serialMsg)["time"] == "8"){
                        this->state = WAITING_FOR_OPENING;
                    }
                    //if time == 19.00
                    if((*this->serialMsg)["time"] == "19"){
                        this->state = WAITING_FOR_CLOSING;
                    }
                }
            }
            
            if(this->readBtMessage()){

                String el = (*this->btMsg)["hardware"];
                if(el == "LED"){
                    //if switch to ON
                    if((*this->btMsg)["state"]){
                        this->setLedON();
                    }
                    //if switch to OFF
                
                    if(!(*this->btMsg)["state"]){
                        this->setLedOFF();
                    }
                }else if (el == "SERVOMOTOR"){
                        this->setAngle((*this->btMsg)["angle"]);
                    }
                }
            
            
            break;
        case WAITING_FOR_OPENING: 
            //if movement detected == true
            if(this->readSerialMessage() && (*this->serialMsg)["inside_room"])
            {
                //open roller blinds then going back to RUNNING
                this->servo->open();
                this->state = RUNNING;
            }
            break;
        case WAITING_FOR_CLOSING:
            //if movement detected == false
            if(this->readSerialMessage() && !(*this->serialMsg)["inside_room"]){
                //close roller blinds then going back to RUNNING
                this->servo->close();
                this->state = RUNNING;
            }
            break;
    }
}