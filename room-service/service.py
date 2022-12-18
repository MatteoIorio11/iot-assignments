import random
from flask import Flask
from flask import request
from paho.mqtt import client as mqtt_client
from threading import Thread
import json
from datetime import datetime
import time 
import serial

# ==================== SETUP THE SERVER
app = Flask(__name__)
# ==================== SETUP ARDUINO
#arduino = serial.Serial(port='COM4', baudrate=115200, timeout=.1)
LED_TAG = "LED"
SERVO_TAG = "SERVOMOTOR"
TIME_TAG = "TIME"
PIR_TAG = "PIR"
#components[0] = Servo's angle
#components[1] = Led's state
#components[2] = PIR's relevation
components = list()
#writes[0] = writeServo
#writes[1] = writeLed
writes = list()

# ==================== SETUP MQTT
broker = 'broker.mqtt-dashboard.com'
port = 1883
topic = "esp-light"
# ==================== generate client ID with pub prefix randomly
client_id = f'python-mqtt-{random.randint(0, 100)}'
# ==================== total time on
#times[0] = start time led on
#times[1] = total time
times = list()


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


def subscribe(client: mqtt_client, total_t: int, start_t: int, res: list, w:list):
    def on_message(client, userdata, msg):
        print(f"Received `{msg.payload.decode()}` from `{msg.topic}` topic")
        json_message = json.loads(msg.payload.decode())
        calcTime(json_message, total_t, start_t, res, w)
                

    client.subscribe(topic)
    client.on_message = on_message


### Calculate the difference between the initial time ON and the last time OFF
def calcTime(json_message: dict, total_t: int, start_t: int, res: list, w:list):
    total_time = total_t
    start_time = start_t
    w[2] = True
    if json_message["inside_room"] == False:
            components[2] = False
            total_time += get_sec(json_message["time"]) - res[0]
            res[1] += total_time
    else:
        components[2] = True
        if json_message["state"] == "ON":
            #get the start's seconds of the LED ON 
            start_time = get_sec(json_message["time"])
            res[0] = start_time
        else:
            if(res[0] > 0):
                total_time += get_sec(json_message["time"]) - res[0]
                res[1] += total_time
    

### CONVERT HH:MM:SS into seconds
def get_sec(time_str):
    h, m, s = time_str.split(':')
    return int(h) * 3600 + int(m) * 60 + int(s)


@app.route('/api/data', methods = ['GET'])
def handlerSeconds():
    #return the values to the Room Dashboard
    if request.method == 'GET':
        j = json.dumps({'seconds': times[1]})
        resp = Flask.make_response(app,j)
        resp.headers['ContentType'] = 'application/json'
        resp.headers['Access-Control-Allow-Origin'] = '*'
        return resp


@app.route('/api/servo', methods=['GET', 'POST'])
def handlerServo():
    if request.method == 'GET':
        angle = request.args.get('angle')
        if angle != None:
            components[0] = angle
            writes[0] = True # Arduino has to write

        # Send the message to the Client
        j = json.dumps({'angle': components[0]})
        resp = Flask.make_response(app,j)
        resp.headers['ContentType'] = 'application/json'
        resp.headers['Access-Control-Allow-Origin'] = '*'
        return resp

@app.route('/api/led', methods=['GET', 'POST'])
def handlerLed():
    if request.method == 'GET':
        state = request.args.get('state')
        if state != None:
            components[1] = False if state == "OFF" else True
            writes[1] = True # Arduino has to write
        
        # Send the message to the Client
        j = json.dumps({'state': "ON" if components[1] == True else "OFF"})
        resp = Flask.make_response(app,j)
        resp.headers['ContentType'] = 'application/json'
        resp.headers['Access-Control-Allow-Origin'] = '*'
        return resp



def startClient():
    client = connect_mqtt()
    subscribe(client, times[0], times[1], times, writes)
    client.loop_forever()    

def startServer():
    app.run(debug=False, host='127.0.0.100',port=5000)

def startArduino():
    
    curr_hour, curr_min, curr_sec  = str(datetime.now().time()).split(':')
    while True:
        if(int(curr_hour) == 8 and int(curr_min) == 0 and int(curr_sec) == 0):
            j = json.dumps({'hardware': TIME_TAG, 'time': "8", 'state':components[1], 'angle':components[0], 'inside_room':components[2]})
            print(j)
        elif (int(curr_hour) == 19 and int(curr_min) == 0 and int(curr_sec) == 0):
            j = json.dumps({'hardware':TIME_TAG, 'time': "19", 'state':components[1], 'angle':components[0], 'inside_room':components[2]})
        #if(arduino.inWaiting() > 0):
            #read the message
            #msg = arduino.readline()
            #msg_dese = json.loads(msg)
            #save the infos about Servo and Led inside a variable and the there will be a button inside the Dashboard
            #such as Refresh, and It will return the infos about
        if (writes[1]):
            j = json.dumps({'hardware':LED_TAG, 'time': curr_hour, 'state':components[1], 'angle':components[0], 'inside_room':components[2]})
            print("Send data to arduino")
            #invia un msg contenente le info del led
            writes[1] = False
            #arduino.write(bytes(j, 'utf-8'))
        if (writes[0]):
            j = json.dumps({'hardware':SERVO_TAG, 'time': curr_hour, 'state':components[1], 'angle':components[0], 'inside_room':components[2]})
            print(j)
            #invia un msg contentente le info del servo
            writes[0] = False
            #arduino.write(bytes(j, 'utf-8'))
        if (writes[2]):
            j = json.dumps({'hardware':PIR_TAG, 'time': curr_hour, 'state':components[1], 'angle':components[0], 'inside_room':components[2]})
            writes[2] = False
            print(j)
        
        time.sleep(2)
        
        

def run():
    times.append(0)
    times.append(0)
    writes.append(False) # Write Servo's information
    writes.append(False) # Write Led's information
    writes.append(False) # Write PIR's information
    components.append(0)
    components.append(False)
    components.append(False)
    
    mqtt_thread = Thread(target=startClient)
    server_thread = Thread(target=startServer)
    #arduino_thread = Thread(target=startArduino)
    mqtt_thread.start()
    server_thread.start()
    arduino_thread.start()
    


if __name__ == '__main__':
    run()