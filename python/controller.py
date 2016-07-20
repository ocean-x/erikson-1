# OCEANX
# This is a GUI visualisation program for the Bosch 9 axes motion shield sensor
# Tested on the Arduino Mega 2560 and the Raspberry Pi 2 B+

# This script needs vPython, pyserial and pywin modules
# I recommend you use Python 2.6.4 or Python 2.7; Python 3 does not work here

# TODO Install pywin from http://sourceforge.net/projects/pywin32/
#      Install pyserial from http://sourceforge.net/projects/pyserial/files
#      Install vPython from http://vpython.org/contents/download_windows.html
#      We still need to find a way to open a serial connection between the Pi and the Arduino
# Moving beyond that, a network connection between the Pi and the computer. Platform IO, ROS or Telemus will serve as good starting points for research

from visual import*
import serial
import string
import math
import msvcrt
import time

from time import time
gradtorad = 3.141592/180.0

# (On Windows) Check your COM port and serial baud rate
# (On Mac OS or Linux) pray I find a solution in time

ser = serial.Serial(port = 'COM16', baudrate = 15200)

# Main scene
 
