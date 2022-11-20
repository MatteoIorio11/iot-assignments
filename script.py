import serial
import json
import time
from matplotlib import animation
import random as rnd

import matplotlib.pyplot as plt
from matplotlib.widgets import Slider, Button, RadioButtons

fig = plt.figure(figsize = (8,8))            
subplot = fig.add_subplot()
subplot._axis3don = False  
axfreq = plt.axes([0.25, 0, 0.60, 0.03])

sfreq = Slider(axfreq, 'Freq', 0, 180.0, valinit=0, valstep=1)


def update(val):
    freq = sfreq.val
    print(freq)


sfreq.on_changed(update)

#arduino = serial.Serial(port='/dev/ttyACM0', baudrate=9600)
count = 0
x=[]
y=[]

def myFunction(i):
    global count
    count +=1

    x.append(count)
    y.append(rnd.randint(1,10))
    a = subplot.cla() 
    subplot.plot(x,y)




anima = animation.FuncAnimation(plt.gcf(), myFunction, interval=1500)

plt.show()
