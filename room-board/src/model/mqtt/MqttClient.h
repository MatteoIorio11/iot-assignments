#ifndef __MQTTCLIENT__
#define __MQTTCLIENT__

#include <WiFi.h>
#include <PubSubClient.h>
#include "constants/Constants.h"


class MqttClient{
    private:
        const char* mqtt_server = MQTT_SERVER;
        const char* topic = MQTT_TOPIC;
        PubSubClient *client;
        void connect();
    public:
        MqttClient();
        void sendMessage(String msg);
};

#endif