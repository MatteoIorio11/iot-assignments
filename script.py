import serial
import json
from matplotlib import animation
import random as rnd
import matplotlib.pyplot as plt
from tkinter import *

arduino = serial.Serial(port='/dev/ttyACM0', baudrate=9600, timeout=.1)

def show_values(value=None):
    #print(w.get())
    x = {
        "angle": w.get()
        }
    y = json.dumps(x)
    #print(y)
    arduino.write(y)

    

master = Tk()
w = Scale(master, from_=0, to=100, orient=HORIZONTAL, command=show_values)
w.pack()
count = 0
x=[]
y=[]

def myFunction(i):
    global count
    count +=1

    if(arduino.inWaiting() > 0):
        try:
            msg = arduino.readline()
            j = json.loads(msg)
            print(j)
            val = j['waterLevel']*100
            print(val)
            int_k = int(val)
            x.append(count)
            y.append(int_k)
            plt.cla()
            plt.plot(x,y)
        except:
            print("")


anima = animation.FuncAnimation(plt.gcf(), myFunction, interval=10)
plt.show()
