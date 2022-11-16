import serial
import json
import time


arduino = serial.Serial(port='/dev/ttyACM0', baudrate=9600)

def main():
    while True:
        if(arduino.inWaiting() > 0):
            input = arduino.readline()
            jsonFromatted = json.loads(input)
            print(jsonFromatted)

if __name__ == "__main__":
    main()

