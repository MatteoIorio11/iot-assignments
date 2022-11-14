import serial
import json
import random as rnd
import matplotlib.pyplot as chart
import time

#arduino = serial.Serial(port='COM4', baudrate=9600, timeout=.1)

# GRAFICO 
# SLIDER/HANDLER_KEYBOARD/BUTTONS

import matplotlib.pyplot as plt
import numpy

hl, = plt.plot([], [])

def update_line(hl, new_data):
    hl.set_xdata(numpy.append(hl.get_xdata(), new_data))
    hl.set_ydata(numpy.append(hl.get_ydata(), new_data))
    plt.draw()

def main():
    x = [1,2,3,4,5,6,7,8,9] #time
    y = [1.1,1.2,4.5,1,6,5,3,1.8, 1] #vals
    i = 10
    while True:
        x.append(i)
        y.append(rnd.randint(1,100))
        chart.plot(x,y)
        time.sleep(1)
        i+=1
        if(i == 100):
            break
    #while True:
    #    val = arduino.read()
    #    message = json.loads(val)

if __name__ == "__main__":
    main()

