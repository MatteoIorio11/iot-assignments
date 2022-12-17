import random
from flask import Flask
from flask import request
from paho.mqtt import client as mqtt_client
from threading import Thread
import json
from datetime import datetime
import serial

# ==================== SETUP THE SERVER
app = Flask(__name__)
# ==================== SETUP ARDUINO
#arduino = serial.Serial(port='COM4', baudrate=115200, timeout=.1)
# ==================== SETUP MQTT
broker = 'broker.mqtt-dashboard.com'
port = 1883
topic = "esp-light"
# ==================== generate client ID with pub prefix randomly
client_id = f'python-mqtt-{random.randint(0, 100)}'
# ==================== total time on
time = 0
start_time = 0


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
        calcTime(json.loads(msg.payload.decode()))
                

    client.subscribe(topic)
    client.on_message = on_message


@app.route('/api/data', methods = ['GET', 'POST'])
def handler():
    #return the values to the Room Dashboard
    if request.method == 'GET':
        j = json.dumps({'PythonSays':'ciao'})
        resp = Flask.make_response(app,j)
        resp.headers['ContentType'] = 'application/json'
        resp.headers['Access-Control-Allow-Origin'] = '*'
        return resp
    if request.method == 'POST':
        #write to arduino using the serial line
        n = 0
        return "write to arduino"


def startClient():
    client = connect_mqtt()
    subscribe(client)
    client.loop_forever()    

def startServer():
    app.run(debug=False, host='127.0.0.100',port=5000)

def run():
    t1 = Thread(target=startClient)
    #t2 = Thread(target=startServer)
    t1.start()
    #t2.start()
    
### Calculate the difference between the initial time ON and the last time OFF
def calcTime(json_message: dict):
    if json_message["inside_room"] == False:
        print("")
    else:
        if json_message["state"] == "ON":
            #get the 
            start_time = get_sec(json_message["time"])
        else:
            time += get_sec(json_message["time"]) - start_time
            print(str(time))

### CONVERT HH:MM:SS into seconds
def get_sec(time_str):
    h, m, s = time_str.split(':')
    return int(h) * 3600 + int(m) * 60 + int(s)

if __name__ == '__main__':
    run()