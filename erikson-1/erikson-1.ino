/*
OCEANX CONTROL SYSTEM
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

	Serial.println("OCEANX CONTROL SYSTEM");
	Serial.println("Please place ROV on a flat surface");
	delay(1000);

	I2C.begin(); //for the 9-axis motion sensor?
	delay(2000);

	/*
	Initialise the three sensors here

	*/
	delay(30);
	/*
	Take some readings and offset the values here

	*/
	Serial.println("Offset: ");
	for (int y = 0; y < 6; y++)
		Serial.println(AN_OFFSET[y]);
	delay(1000);
	digitalWrite(lightPin, LOW);
	Serial.println("");
	Serial.println("");
	Serial.println("");
	Serial.println("");
	Serial.println("");
	Serial.println("");
	Serial.println("");
	Serial.println("");
	Serial.println("");
	delay(1000); // another pause

	timer = millis(); 
	delay(20);
	counter = 0;


}

void loop() {

}


void forward() {

}

void backward() {

}

void ascend() {

}

void descend() {

}

void turnLeft() {

}

void turnRight() {

}

void tiltUp() {

}

void tiltDown() {

}

//this function stops all motors
void stopALL() {
	Serial.println("STOPPING ALL MOTORS!");

}
