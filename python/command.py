# OCEANX BASE STATION CONTROL SYSTEM –
# Tested with Raspberry Pi
# Windows verion

import time
import serial

#configure the serial connections (the device you are connecting to)
#this configuration is meant for a base station running Windows
ser = serial.Serial(port = '/dev/COM4', baudrate = 115200)

ser.open()
ser.isOpen()

print 'Enter your commands below.\r\nInsert "exit" to leave the application'

input = 1

while 1 :
    # get keyboard input
    input = raw_input(">> ")
        # For Python 3 users
        # input = input(">> ")
    if input = 'exit' :
        ser.close()
        exit()
    else :
        # send the character to the device
        ser.write(input + '\r\n')
        out = ''
        # let's wait one second before reading output (give ROV time to answer)
        time.sleep(1)
        while ser.inWaiting() > 0 :
            out += ser.read(1)

        if out != '':
            print ">>" + out
