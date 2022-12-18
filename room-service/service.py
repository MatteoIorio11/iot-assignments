import random
from flask import Flask
from flask import request
from paho.mqtt import client as mqtt_client
from threading import Thread
import json
import serial

# ==================== SETUP THE SERVER
app = Flask(__name__)
# ==================== SETUP ARDUINO
#arduino = serial.Serial(port='COM4', baudrate=115200, timeout=.1)
servo_angle = 0
led_state = False
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


def subscribe(client: mqtt_client, total_t: int, start_t: int, res: list):
    def on_message(client, userdata, msg):
        print(f"Received `{msg.payload.decode()}` from `{msg.topic}` topic")
        json_message = json.loads(msg.payload.decode())
        calcTime(json_message, total_t, start_t, res)
                

    client.subscribe(topic)
    client.on_message = on_message


### Calculate the difference between the initial time ON and the last time OFF
def calcTime(json_message: dict, total_t: int, start_t: int, res: list):
    total_time = total_t
    start_time = start_t
    if json_message["inside_room"] == False:
            total_time += get_sec(json_message["time"]) - res[0]
            res[1] += total_time
    else:
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
            j = json.dumps({'angle': angle})
            print("Send data to arduino")
            servo_angle = angle
            #arduino.write(bytes(j, 'utf-8'))

        j = json.dumps({'angle': servo_angle})
        resp = Flask.make_response(app,j)
        resp.headers['ContentType'] = 'application/json'
        resp.headers['Access-Control-Allow-Origin'] = '*'
        return resp

@app.route('/api/led', methods=['GET', 'POST'])
def handlerLed():
    if request.method == 'GET':
        state = request.args.get('state')
        if state != None:
            j = json.dumps({"state":state})
            print("Send data to arduino")
            led_state = state
            #arduino.write(bytes(j, 'utf-8'))
        
        j = json.dumps({'state': led_state})
        resp = Flask.make_response(app,j)
        resp.headers['ContentType'] = 'application/json'
        resp.headers['Access-Control-Allow-Origin'] = '*'
        return resp



def startClient():
    client = connect_mqtt()
    subscribe(client, times[0], times[1], times)
    client.loop_forever()    

def startServer():
    app.run(debug=False, host='127.0.0.100',port=5000)

def startArduino():
    while True:
        if(arduino.inWaiting() > 0):
            #read the message
            msg = arduino.readline()
            msg_dese = json.loads(msg)
            #save the infos about Servo and Led inside a variable and the there will be a button inside the Dashboard 
            #such as Refresh, and It will return the infos about 
        
        

def run():
    times.append(0)
    times.append(0)
    
    #mqtt_thread = Thread(target=startClient)
    server_thread = Thread(target=startServer)
    #arduino_thread = Thread(target=)
    #mqtt_thread.start()
    server_thread.start()
    


if __name__ == '__main__':
    run()