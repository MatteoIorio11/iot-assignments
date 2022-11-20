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

sfreq = Slider(axfreq, 'Freq', 0, 180.0, valinit=0, valstep=1)


<<<<<<< HEAD
arduino = serial.Serial(port='/dev/ttyACM0', baudrate=9600, timeout=.1)

def show_values(value=None):
    #print(w.get())
    x = {
        "angle": w.get()
        }
    y = json.dumps(x)
    #print(y)
    arduino.write(y)
=======
def update(val):
    freq = sfreq.val
    print(freq)
>>>>>>> 1e4517f15dd458eb1385bfa526876b91966d64d7


<<<<<<< HEAD
master = Tk()
w = Scale(master, from_=0, to=100, orient=HORIZONTAL, command=show_values)
w.pack()
=======
sfreq.on_changed(update)

#arduino = serial.Serial(port='/dev/ttyACM0', baudrate=9600)
>>>>>>> 1e4517f15dd458eb1385bfa526876b91966d64d7
count = 0
x=[]
y=[]

def myFunction(i):
    global count
    count +=1

<<<<<<< HEAD
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
=======
    x.append(count)
    y.append(rnd.randint(1,10))
    a = subplot.cla() 
    subplot.plot(x,y)




anima = animation.FuncAnimation(plt.gcf(), myFunction, interval=1500)

>>>>>>> 1e4517f15dd458eb1385bfa526876b91966d64d7
plt.show()
