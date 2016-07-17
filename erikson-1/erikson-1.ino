/*
OCEANX CONTROL SYSTEM –
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

//sensor stuff
NAxisMotion ROVSensor;
unsigned long lastStreamTime = 0;
const int streamPeriod = 40; //stream at 25Hz, which is 1000/40
bool updateSensorData = true;

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

//internal sensors
const int waterdetectPin = 3;
const int pressurePin =4;
const int internaltemperaturePin = 2;


// may need tweaking
// depending on choice of ESC TODO
int LFstop = 93;
int stopMotor = 96;

int turningSpeed = 25;
int horizontalSpeedIncrement = 5;
int speedIncrement = 2;
int speedAdjustment = 1;
int speedDecrease = 1;

long timer = 0; //general purpose timer
int state = ' ';
int waterlevel = 0; //for waterDetect

void setup() {
	Serial.begin(115200);

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
	detectWater();

	Serial.println("OCEANX CONTROL SYSTEM");
	Serial.println("Please place ROV on a flat surface");
	delay(1000);

	I2C.begin(); //for the 9-axis motion sensor?
	delay(2000);

	//displaying the keyboard mappings
	Serial.println("Welcome to OceanX!");
	Serial.println("Enter a command!");
	Serial.println("Keyboard (Xbox controller functionality will come later):");
	Serial.println("I - Ascend");
	Serial.println("K - Descend");
	Serial.println("W - Forward");
	Serial.println("A – Rotate Left");
	Serial.println("S – Backward");
	Serial.println("D – Rotate Right");
	Serial.println("X – Stop");
	Serial.println("T – Tilt Up");
	Serial.println("G – Tilt Down");
	Serial.println("L – Toggle Lights");
	delay(1000); // another pause


	//initialise the three sensors here
	ROVSensor.initSensor();
	ROVSensor.setOperationMode(OPERATION_MODE_NDOF); // or 0x0C, can be set to debug
	ROVSensor.setUpdateMode(MANUAL); //default is auto, manual has to update function before read function
	//manual has lesser reads to sensor
	mySensor.updateAccelConfig();
  updateSensorData = true;
  Serial.println();
  Serial.println("Default accelerometer configuration settings...");
  Serial.print("Range: ");
  Serial.println(mySensor.readAccelRange());
  Serial.print("Bandwidth: ");
  Serial.println(mySensor.readAccelBandwidth());
  Serial.print("Power Mode: ");
  Serial.println(mySensor.readAccelPowerMode());
  Serial.println("Streaming in ...");	//Countdown
  Serial.print("3...");
  delay(1000);	//Wait for a second
  Serial.print("2...");
  delay(1000);	//Wait for a second
  Serial.println("1...");
  delay(1000);	//Wait for a second

	digitalWrite(lightPin, LOW); //turning the light off becuase we've tested it I guess?



	timer = millis(); //remember to declare that such a thing exists
	delay(20);
	counter = 0;

}

int go_l;
int go_r;
char key; //keyboard

void loop() {

	//reading keyboard
	while (Serial.available()) {
		delay(1);
		key = (char)Serial.read();
		switch (key) {

			case 'k' : descend();
				Serial.println("Descending");
				break;

			case 'i' : ascend();
				Serial.println("Ascending");
				break;

			case 'w' : forward();
				Serial.println("Moving forward");
				break;

			case 's' : backward();
				Serial.println("Moving backward");
				break;

			case 'a' : turnLeft();
				Serial.println("Turning left");
				break;

			case 'd' : turnRight();
				Serial.println("Turning right");
				break;

			case 'i' : toggleLights();
				break;

			case ' ' : stopALL();
				break;

			case 't' : tiltUp();
				Serial.println("Tiling up");
				break;

			case 'g' : tiltDown();
				Serial.println("Tilting down");
				break;

		}
	}

}


void forward() {
	if (state == 'w') {
		go_l = go_l + horizontalSpeedIncrement;
		go_r = go_r + horizontalSpeedIncrement;
		//ESC_LEFT_BACK_VERT.write(LFstop);
		//ESC_LEFT_FRONT_VERT.write(stopMotor);
		//ESC_RIGHT_BACK_VERT(stopMotor);
		//ESC_RIGHT_FRONT_VERT(stopMotor);
		ESC_LEFT_HORIZ.write(go_l);
		ESC_RIGHT_HORIZ.write(go_r);
	} else {
		go_l = 111; // CALIBRATE!!!
		go_r = 113; // TODO
		ESC_LEFT_HORIZ.write(go_l);
		ESC_RIGHT_HORIZ.write(go_r);
		//ESC_LEFT_BACK_VERT.write(LFstop);
		//ESC_LEFT_FRONT_VERT.write(stopMotor);
		//ESC_RIGHT_BACK_VERT(stopMotor);
		//ESC_RIGHT_FRONT_VERT(stopMotor);
		state = 'w';
	}

}

void backward() {
	if (state == 's') {

	}

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

void toggleLights() {
	switch (lightEnable) {
		case true : digitalWrite(lightPin, LOW);
			Serial.println("Lights off");
			lightEnable = false;
			break;
		case false : digitalWrite(lightPin, HIGH);
			Serial.println("Lights on");
			lightEnable = true;
			break;
	}

}

//this function stops all motors
void stopALL() {
	Serial.println("STOPPING ALL MOTORS!");

}

void detectWater() {
	waterlevel = analogRead(waterdetectPin);
	if (waterlevel > 400) { // judgement variable for water detection
		digitalWrite(lightPin, HIGH);
		ascend();
		Serial.prinln("LEAK DETECTED! ABORTING.")
	} else {
		delay(100);
	}

}
