import serial
import json
import time


arduino = serial.Serial(port='/dev/ttyACM0', baudrate=9600)

def main():
    while True:
	    print(str(arduino.readline()))

if __name__ == "__main__":
    main()

