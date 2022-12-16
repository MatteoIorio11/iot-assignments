#include "MqttClient.h"

static WiFiClient espClient;

MqttClient::MqttClient(){
    randomSeed(micros());
    this->client = new PubSubClient(espClient);
    this->setupWIFI();
    this->connectWIFI();
    this->client->setServer(this->mqtt_server, MQTT_PORT);
}

void MqttClient::connectWIFI(){
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        //Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

void MqttClient::setupWIFI(){
    WiFi.mode(WIFI_STA);
    WiFi.begin(this->ssid, this->password);
}

/// @brief Connect the Client to the Mqtt's Broker
void MqttClient::connect(){
    while (!this->client->connected()) {
        Serial.print("Attempting MQTT connection...");
        String clientId = String(MQTT_CLIENTNAME)+String(random(0xffff), HEX);
        if (this->client->connect(clientId.c_str())) {
            Serial.println("connected");
            this->client->subscribe(this->topic);
        } else {
            Serial.print("failed, rc=");
            //Serial.print(client.state());
            //Serial.println(" try again in 5 seconds");
            // Wait 5 seconds before retrying
            delay(5000);
        }
    }
}

/// @brief Send the message to the broker
/// @param msg JSON file
void MqttClient::sendMessage(String msg){
    if(!this->client->connected()){
        this->connect();
    }
    // Length (with one extra character for the null terminator)
    int str_len = msg.length() + 1;
    // Prepare the character array (the buffer) 
    char output[str_len];
    // Copy it over 
    msg.toCharArray(output, str_len);
    this->client->publish(this->topic, output);
}