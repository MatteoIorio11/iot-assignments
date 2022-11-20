import serial
import json
from matplotlib import animation
import random as rnd

import matplotlib.pyplot as plt
from matplotlib.widgets import Slider, Button, RadioButtons

fig = plt.figure(figsize = (8,8))            
subplot = fig.add_subplot()
subplot._axis3don = False  
axfreq = plt.axes([0.25, 0, 0.60, 0.03])

sfreq = Slider(axfreq, 'Angle', 0, 180.0, valinit=0, valstep=1)
arduino = serial.Serial(port='/dev/ttyACM0', baudrate=9600)

def add(val):
    
    if button.color == 'red':
        x = {
            "control": 0
        }
        y = json.dumps(x)
        arduino.write(bytes(y, 'utf-8'))
        button.color = 'green'
    else:
         x = {
            "control": 1
        }
        y = json.dumps(x)
        button.color = 'red'
        arduino.write(bytes(y, 'utf-8'))
 
# defining button and add its functionality
axes = plt.axes([0.81, 0.000001, 0.1, 0.075])
button = Button(axes, 'Add',color="red")
button.on_clicked(add)
def update(val):
    freq = sfreq.val
    x = {
        "angle": freq
    }
    y = json.dumps(x)
    arduino.write(bytes(y, 'utf-8'))


sfreq.on_changed(update)

count = 0
x=[]
y=[]

def myFunction(i):
    global count
    count +=1

    if(arduino.inWaiting() > 0):
        try:
            msg = arduino.readline()
            print(msg)
            json_parsed = json.loads(msg)
            water_level = int(json_parsed['waterLevel']*100)
            angle = int(json_parsed['angle'])
            if len(x) == 30:
                x.pop(0)
                y.pop(0)
            y.append(water_level)
            x.append(count)
            subplot.cla() 
            subplot.plot(x,y)
        except Exception as e:
            count-=1


anima = animation.FuncAnimation(plt.gcf(), myFunction, interval=10)
plt.show()

arduino.write("START")
