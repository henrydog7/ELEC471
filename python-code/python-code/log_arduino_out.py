# Log the output from an Arduino to a text file
# The Arduino should be programmed to send data over Serial
# This script connects to the Arduino's serial port and logs the data

import serial     # Import the pySerial library!


""" User Configurable Parameters """
arduino_port = "/dev/ttyACM0"   # On Windows: "COMx", On Mac: "/dev/cu.usbmodemxxx"
fileName = "Arduino_out.txt"    # Output file name
baud = 115200                   # Baud rate; must match the rate in the Arduino code
num_lines = 100                 # Number of lines to collect from the serial port


ser = serial.Serial(arduino_port, baud)
print("Connected to Arduino port: " + arduino_port)

with open(fileName, "w") as file:
    line = 0
    while line <= num_lines:
        data=ser.readline().decode("utf-8").strip()
        print(data)
        
        file.write(data + "\n")
        line = line + 1

ser.close()
print("Data collection complete!")

