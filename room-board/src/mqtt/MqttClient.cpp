#include "MqttClient.h"

MqttClient::MqttClient(char* mqtt_server, char* topic){
    this->mqtt_server = mqtt_server;
    this->topic = topic;
      randomSeed(micros());
    this->connect();
}

/// @brief Connect the Client to the Mqtt's Broker
void MqttClient::connect(){
    while (!this->client->connected()) {
        //Serial.print("Attempting MQTT connection...");
        String clientId = String("esiot-2122-client-")+String(random(0xffff), HEX);
        if (this->client->connect(clientId.c_str())) {
            //Serial.println("connected");
            this->client->subscribe(this->topic);
            } else {
            //Serial.print("failed, rc=");
            //Serial.print(client.state());
            //Serial.println(" try again in 5 seconds");
            // Wait 5 seconds before retrying
            delay(5000);
        }
    }
}

/// @brief Send the message to the broker
/// @param msg JSON file
void MqttClient::sendMessage(char *msg){
    if(!this->client->connected()){
        this->connect();
    }
    this->client->publish(this->topic, msg);
}