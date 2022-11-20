import time
import matplotlib.pyplot as plt
import json
import serial

arduino = serial.Serial(port='/dev/ttyACM0', baudrate=9600, timeout=.1)
arduino.flush()

def main():
    
    while True:
        if(arduino.inWaiting() > 0):
            msg = arduino.readline()
            j = json.loads(msg)
            print(j)

if __name__ == "__main__":
    main()