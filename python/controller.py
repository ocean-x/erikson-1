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
scene = display(title = "OCEANX ROV")
scene.range = (1.2, 1.2, 1.2)
scene.forward = (1, 0, -0.25)
scene.up = (0, 0, 1)

#Second scene (display of roll, pitch and yaw)
scene2 = display(title = "OCEANX ROV", x=0, y=0, width=500, height=200, center=(0,0,0), background=(0,0,0))
scene2.range = (1, 1, 1)
scene.width = 500
scene.y = 200

scene3 = display(title = 'Control Panel', x=0, y=0, width=500, height=200, center=(0,0,0), background=(0,0,0))
scene3.range(1, 1, 1)

scene2.select()

#Meters for roll, pitch and yaw)
cil_roll = cylinder(pos=(-0.4,0,0),axis=(0.2,0,0),radius=0.01,color=color.red)
cil_roll2 = cylinder(pos=(-0.4,0,0),axis=(-0.2,0,0),radius=0.01,color=color.red)
