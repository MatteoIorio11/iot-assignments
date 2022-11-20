import serial
import json
import time
from matplotlib import animation
import random as rnd
import matplotlib.pyplot as plt

arduino = serial.Serial(port='/dev/ttyACM1', baudrate=9600)


def main():
    msg = "ciao"
    arduino.write(bytes(msg, 'utf-8'))


if __name__ == "__main__":
    main()