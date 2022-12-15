import random
from flask import Flask
from flask import request
from paho.mqtt import client as mqtt_client
from threading import Thread
import serial

#SETUP THE SERVER
app = Flask(__name__)
#SETUP ARDUINO
#arduino = serial.Serial(port='COM4', baudrate=115200, timeout=.1)
#SETUP MQTT
broker = 'broker.mqtt-dashboard.com'
port = 1883
topic = "esp-light"
# generate client ID with pub prefix randomly
client_id = f'python-mqtt-{random.randint(0, 100)}'


def connect_mqtt() -> mqtt_client:
    def on_connect(client, userdata, flags, rc):
        if rc == 0:
            print("Connected to MQTT Broker!")
        else:
            print("Failed to connect, return code %d\n", rc)
    client = mqtt_client.Client(client_id)
    client.on_connect = on_connect
    client.connect(broker, port)
    return client


def subscribe(client: mqtt_client):
    def on_message(client, userdata, msg):
        print(f"Received `{msg.payload.decode()}` from `{msg.topic}` topic")

    client.subscribe(topic)
    client.on_message = on_message


@app.route('/', methods = ['GET', 'POST'])
def handler():
    #return the values to the Room Dashboard
    if request.method == 'GET':
        #return values to the dashboard
        a = 0
        return "return to the client a json file"
    if request.method == 'POST':
        #write to arduino using the serial line
        n = 0
        return "write to arduino"


def startClient():
    client = connect_mqtt()
    subscribe(client)
    client.loop_forever()    

def startServer():
    app.run(debug=False, host='127.0.0.100')

def run():
    t1 = Thread(target=startClient)
    t2 = Thread(target=startServer)
    t1.start()
    t2.start()

if __name__ == '__main__':
    run()