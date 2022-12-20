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
        Serial.println(msg->getContent());
        char ar [256];  
        msg->getContent().toCharArray(ar, msg->getContent().length());
        deserializeJson(*this->btMsg, ar); //deserializing of te JSON
        delete msg;
        return true;
    }else{
        return false;
    }
}
int angle;
/// @brief State Machine of the RoomController
void RoomController::tick(){
    
    switch (this->state)
    {
        case RUNNING:
            //if we don't have any new message we don't do anything
            //Serial.println("RUNNING");
            if(this->readSerialMessage())
            {
                String el = (*this->serialMsg)["hardware"];
                if(el =="LED"){
                    Serial.println("LED");
                    if((*this->serialMsg)["state"]){
                        this->state = SETTING_LED_ON;
                    }
                    //if switch to OFF
                    if(!(*this->serialMsg)["state"]){
                        this->state = SETTING_LED_OFF;
                    }
                }else if(el == "SERVOMOTOR"){
                    angle = (int)((*this->serialMsg)["angle"]);
                    Serial.println(angle);
                    this->state = SETTING_ANGLE;
                }else if(el == "PIR"){
                    if((*this->serialMsg)["lum"]){
                        this->state = SETTING_LED_ON;
                    }else{
                        this->state = SETTING_LED_OFF;
                    }
                } else if(el == "TIME"){
                    //Serial.print("HHHH");
                    //if time == 8.00
                    if((*this->serialMsg)["time"] == "8"){
                        this->state = WAITING_FOR_OPENING;
                    }
                    //if time == 19.00
                    if((*this->serialMsg)["time"] == "19"){
                        //this->state = WAITING_FOR_CLOSING;
                    }
                }
            }
            
            if(this->readBtMessage()){

                String el = (*this->btMsg)["hardware"];
                if(el == "LED"){
                    //if switch to ON
                    if((*this->btMsg)["state"]){
                        this->state = SETTING_LED_ON;
                    }
                    //if switch to OFF
                
                    if(!(*this->btMsg)["state"]){
                        this->state = SETTING_LED_OFF;
                    }
                }else if (el == "SERVOMOTOR"){
                        angle = (*this->btMsg)["angle"];
                        this->state = SETTING_ANGLE;
                    }
                }
            
            
            break;
        case WAITING_FOR_OPENING:
            //Serial.println("WAITINGFOROPENING");    
            //if movement detected == true
            if(this->readSerialMessage() && (*this->serialMsg)["inside_room"])
            {
                this->state = OPENING_ROLLER_BLINDS;
            }
            break;
        case WAITING_FOR_CLOSING:
            //if movement detected == false
            if(this->readSerialMessage() && !(*this->serialMsg)["inside_room"]){
                this->state = CLOSING_ROLLER_BLINDS;
            }
            break;
        case OPENING_ROLLER_BLINDS:
            //open roller blinds then going back to RUNNING
            this->servo->open();
            this->state = RUNNING;
            break;
        case CLOSING_ROLLER_BLINDS:
            //close roller blinds then going back to RUNNING
            this->servo->close();
            this->state = RUNNING;
            break;
        case SETTING_LED_OFF:
            //turning the led off then going back to RUNNING
            this->led->ledOff();
            this->state = RUNNING;
            break;
        case SETTING_LED_ON:
            //turning the led on then going back to RUNNING
            this->led->ledOn();
            this->state = RUNNING;
            break;
        case SETTING_ANGLE:
        Serial.println(angle);
            this->servo->setOpening(angle);
            this->state = RUNNING;
            break;
    }

    
}