#ifndef __MQTTCLIENT__
#define __MQTTCLIENT__

#include <WiFi.h>
#include <PubSubClient.h>
#include "constants/Constants.h"


class MqttClient{
    private:
        char* mqtt_server;
        char* topic;
        PubSubClient *client;
        void connect();
    public:
        MqttClient(char* mqtt_server, char* topic);
        void sendMessage(char *msg);
};

#endif