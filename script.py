import serial
import json
import time
from matplotlib import animation
import random as rnd
import matplotlib.pyplot as plt

#arduino = serial.Serial(port='/dev/ttyACM0', baudrate=9600)
count = 0
x=[]
y=[]

def myFunction(i):
    global count
    count +=1

    x.append(count)
    y.append(rnd.randint(1,10))
    plt.cla()
    plt.plot(x,y)




anima = animation.FuncAnimation(plt.gcf(), myFunction, interval=1500)

plt.show()
