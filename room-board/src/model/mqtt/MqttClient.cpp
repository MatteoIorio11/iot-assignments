#include "MqttClient.h"

// I put this here in order to not get the exception : "guru meditation error core 1 panic'ed (loadprohibited). exception was unhandled"
static WiFiClient espClient;

/// @brief Constructor of the MQTT CLIENT
MqttClient::MqttClient(){
    randomSeed(micros());                                 //Random seed for the Client's ID
    this->client = new PubSubClient(espClient);           //Create the PubSubClient
    //this->setupWIFI();                                    //Set Up WIFI
    //this->connectWIFI();                                  //Connect WIFI
    this->client->setServer(this->mqtt_server, MQTT_PORT);//Connect to the MQTT Broker
}

/// @brief Connecto to the WIFI
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

/// @brief SetUp the WIFI, with SSID and Password
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
            Serial.print(this->client->state());
            Serial.println(" try again in 5 seconds");
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