/*
OCEANX MOTOR CALIBRATION SYSTEM –
Tested with Arduino Mega 2560

X Axis pointing forward
Y Axis pointing to the right
Z Axis pointing down
Positive pitch: nose up
Positive roll: right wing down
Positive yaw: clockwise

TODO: Program motion functions
			Add sensor code (once it's been debugged in a separate sketch)
			Start coding Python script
			Test sensors and add them to the main sketch
			Do we want leak detection or not?
			Yes let's start by creating a python file

*/

#include <Servo.h>

#define MAX_SIGNAL 2000
#define MIN_SIGNAL 700
#define MOTOR_PIN 9

Servo motor;

void setup() {

}

void loop() {
  
}
