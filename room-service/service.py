import random
from flask import Flask
from flask import request
from paho.mqtt import client as mqtt_client
from threading import Thread
import threading
import json
from datetime import datetime
import time 
import serial

# ==================== LOCK FOR THREADING
lock = threading.Lock()
# ==================== SETUP THE SERVER
app = Flask(__name__)
# ==================== SETUP ARDUINO
#arduino = serial.Serial(port='/dev/ttyACM0', baudrate=9600)
LED_TAG = "LED"
SERVO_TAG = "SERVOMOTOR"
TIME_TAG = "TIME"
PIR_TAG = "PIR"
#components[0] = Servo's angle
#components[1] = Led's state
#components[2] = PIR's relevation
#components[3] = Photoresistor's value
components = list()
#writes[0] = writeServo
#writes[1] = writeLed
#writes[2] = Pir
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
        #print(f"Received `{msg.payload.decode()}` from `{msg.topic}` topic")
        json_message = json.loads(msg.payload.decode())
        calcTime(json_message, total_t, start_t, res, w)
                

    client.subscribe(topic)
    client.on_message = on_message


### Calculate the difference between the initial time ON and the last time OFF
def calcTime(json_message: dict, total_t: int, start_t: int, res: list, w:list):
    total_time = total_t
    start_time = start_t
    lock.acquire()
    w[2] = True
    lock.release()
    if json_message["inside_room"] == False:
        lock.acquire()
        components[2] = False
        components[3] = False
        lock.release()
        if(res[0] >= 0):
            total_time += get_sec(json_message["time"]) - res[0]
            res[1] += total_time
    else:
        lock.acquire()
        components[2] = True
        lock.release()
        if json_message["state"] == "ON":
            #get the start's seconds of the LED ON 
            start_time = get_sec(json_message["time"])
            res[0] = start_time
            lock.acquire()
            components[3] = True
            lock.release()


        else:
            if(res[0] > 0):
                if(res[0] >= 0):
                    total_time += get_sec(json_message["time"]) - res[0]
                    res[1] += total_time
                    lock.acquire()
                    components[3] = False
                    lock.release()


    

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
            lock.acquire()
            components[0] = angle
            writes[0] = True # Arduino has to write
            lock.release()

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
            lock.acquire()
            components[1] = False if state == "OFF" else True
            writes[1] = True # Arduino has to write
            lock.release()
        
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
    eigth = False   
    seven = False
    while True:
        print(writes[1])
        curr_hour, curr_min, curr_sec  = str(datetime.now().time()).split(':')
        if(int(curr_hour) == 17 and int(curr_min) == 55 and int(float(curr_sec)) == 10 and eigth==False):
            j = json.dumps({'hardware': TIME_TAG, 'time': "8"})
            eigth = True
            seven = False
            #print(j)
            arduino.write(bytes(j, 'utf-8'))
        elif (int(curr_hour) == 19 and int(curr_min) == 0 and int(float(curr_sec)) == 0 and seven == False):
            eigth = False
            seven = True
            j = json.dumps({'hardware':TIME_TAG, 'time': "19"})
            arduino.write(bytes(j, 'utf-8'))
        # Write the Servo's infomrations
        if (writes[0]):
            j = json.dumps({'hardware':SERVO_TAG, 'angle':components[0]})
            #invia un msg contentente le info del servo
            lock.acquire()
            writes[0] = False
            print(j)
            lock.release()
            arduino.write(bytes(j, 'utf-8'))
        # Write the Led's informations
        if (writes[1]):
            j = json.dumps({'hardware':LED_TAG, 'state':components[1]})
            print(j)
            lock.acquire()
            #invia un msg contenente le info del led
            writes[1] = False
            lock.release()
            arduino.write(bytes(j, 'utf-8'))
        # Write the Pir's informations
        if (writes[2]):
            j = json.dumps({'hardware':PIR_TAG, 'inside_room':components[2], 'lum': components[3]})
            lock.acquire()
            writes[2] = False
            lock.release()
            arduino.write(bytes(j, 'utf-8'))
            print(j)
        
        time.sleep(0.1)
        

def initVariables():
    # Variables used inside the calc of the total seconds 
    times.append(-1)
    times.append(0)
    # Variables used for communicate with Arduino
    writes.append(False) # Write Servo's information
    writes.append(False) # Write Led's information
    writes.append(False) # Write PIR's information
    # Components of our system
    components.append(0)
    components.append(False)
    components.append(False)
    components.append(False)

def run():

    initVariables()    
    mqtt_thread = Thread(target=startClient)
    server_thread = Thread(target=startServer)
    arduino_thread = Thread(target=startArduino)
    mqtt_thread.start()
    server_thread.start()
    arduino_thread.start()
    


if __name__ == '__main__':
    run()
