/*
OCEANX CONTROL SYSTEM
Tested with Arduino Mega 2560

X Axis pointing forward
Y Axis pointing to the right
Z Axis pointing down
Positive pitch: nose up
Positive roll: right wing down
Positive yaw: clockwise
*/

//libraries
#include <Wire.h>
#include <Servo.h>
#include "NAxisMotion"

//constants, might need to find a more elegant solution using arrays
Servo ESC_LEFT_HORIZ;
Servo ESC_RIGHT_HORIZ;
Servo ESC_LEFT_FRONT_VERT;
Servo ESC_LEFT_BACK_VERT;
Servo ESC_RIGHT_FRONT_VERT;
Servo ESC_RIGHT_BACK_VERT;

//pin assignments: motors, lights, sensors
const int ESC_LEFT_HORIZ_PIN = 5;
const int ESC_LEFT_FRONT_VERT_PIN = 6;
const int ESC_LEFT_BACK_VERT_PIN = 7;

const int ESC_RIGHT_HORIZ_PIN = 8;
const int ESC_RIGHT_FRONT_VERT_PIN = 9;
const int ESC_RIGHT_BACK_VERT_PIN = 10;

const int lightPin = 3;
const int tempPin = 4;
const int pHPin = 5;
boolean lightEnable = false;

void setup() {
	Serial.begin(112500);
	I2C.begin();

	//led on
	pinMode(lightPin, OUTPUT);
	digitalWrite(lightPin, HIGH);

	ESC_LEFT_HORIZ.attach(ESC_LEFT_HORIZ_PIN, 1000, 2000);
	ESC_RIGHT_HORIZ.attach(ESC_RIGHT_HORIZ_PIN, 1000, 2000);
	ESC_LEFT_FRONT_VERT.attach(ESC_LEFT_FRONT_VERT_PIN, 1000, 2000);
	ESC_LEFT_BACK_VERT.attach(ESC_LEFT_BACK_VERT_PIN, 1000, 2000);
	ESC_RIGHT_FRONT_VERT.attach(ESC_RIGHT_FRONT_VERT_PIN, 1000, 2000);
	ESC_RIGHT_BACK_VERT.attach(ESC_RIGHT_BACK_VERT_PIN, 1000, 2000);
	stopALL();



}

void loop() {

}

void stopALL() {
	
}
