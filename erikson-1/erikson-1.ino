/*
OCEANX CONTROL SYSTEM –
Tested with Arduino Mega 2560

X Axis pointing forward
Y Axis pointing to the right
Z Axis pointing down
Positive pitch: nose up
Positive roll: right wing down
Positive yaw: clockwise

TODO: 1. 9 axis motion shield euler angles and compass
      2. internal temperature, humidity and pressure
			3. external temperature
			4. external pH
			5. camera
			6. python script (set up raspberry pi)

*/

//libraries
#include <Wire.h>
#include <Servo.h>
#include <NAxisMotion.h>

float roll;
float pitch;
float yaw;
float heading;
float initHeading;
int SENSOR_SIGN[9]{1, 1, 1, -1, -1, -1, 1, 1, 1};

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
const int tempdetectPin = 4;
const int pHPin = 5;
boolean lightEnable = false;

//internal sensors
const int waterdetectPin = 3;
const int pressurePin = 4;
const int internaltemperaturePin = 2;


// may need tweaking
// depending on choice of ESC TODO
int stopMotor = 96;

int turningSpeed = 25;
int horizontalSpeedIncrement = 5;
int speedIncrement = 2;
int speedAdjustment = 1;
int speedDecrease = 1;

long timer = 0; //general purpose timer
int state = ' ';
int waterlevel = 0; //for waterDetect
int templevel = 0;

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

	I2C.begin(); //for the 9-axis motion sensor?
	delay(2000);
	ROVSensor.initSensor();
	ROVSensor.setOperationMode(OPERATION_MODE_NDOF); // or 0x0C, can be set to debug
	ROVSensor.setUpdateMode(MANUAL); //default is auto, manual has to update function before read function
	//manual has lesser reads to sensor

	Serial.println("OCEANX CONTROL SYSTEM");
	Serial.println("Please rotate ROV for the next 10 seconds");
	while (millis() < 10000) {
		ROVSensor.updateEuler();        //Update the Euler data into the structure of the object
    ROVSensor.updateCalibStatus();  //Update the Calibration Status
    initHeading = ROVSensor.readEulerHeading();
	}
	delay(1000);

	//displaying the keyboard mappings
	Serial.println("Welcome to OceanX!");
	Serial.println("Place ROV on a flat surface facing away from you");
	Serial.println("Enter a command!");
	Serial.println("Keyboard (Xbox controller functionality will come later):");
	Serial.println("I  - Ascend");
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
	ROVSensor.updateAccelConfig();
  updateSensorData = true;
  Serial.println();
  Serial.println("Default accelerometer configuration settings...");
  Serial.print("Range: ");
  Serial.println(ROVSensor.readAccelRange());
  Serial.print("Bandwidth: ");
  Serial.println(ROVSensor.readAccelBandwidth());
  Serial.print("Power Mode: ");
  Serial.println(ROVSensor.readAccelPowerMode());
  Serial.println("Streaming in ...");	//Countdown
  Serial.print("3...");
  delay(1000);	//Wait for a second
  Serial.print("2...");
  delay(1000);	//Wait for a second
  Serial.println("1...");
  delay(1000);	//Wait for a second
	initHeading = ROVSensor.readEulerHeading();
	Serial.print("Initial heading is ");
	Serial.print(initHeading);
	delay(1000);

	digitalWrite(lightPin, LOW); //turning the light off becuase we've tested it I guess?



	timer = millis(); //remember to declare that such a thing exists
	delay(20);
	int counter = 0;

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

			case 'l' : toggleLights();
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

	if (timer - lastStreamTime >= streamPeriod) {
		lastStreamTime = timer;
		ROVSensor.updateEuler();
		ROVSensor.updateCalibStatus();

		Serial.print("Time: ");
    Serial.print(lastStreamTime);
    Serial.print("ms ");

    Serial.print(" Heading: ");
		heading = ROVSensor.readEulerHeading();
    Serial.print(ROVSensor.readEulerHeading()); //Heading data
    Serial.print("deg ");

		Serial.print(" Yaw: ");
		yaw = initHeading - heading;
		Serial.print(yaw);
		Serial.print("deg");

    Serial.print(" Roll: ");
		roll = ROVSensor.readEulerRoll();
    Serial.print(ROVSensor.readEulerRoll()); //Roll data
    Serial.print("deg ");

    Serial.print(" Pitch: ");
		pitch = ROVSensor.readEulerPitch();
    Serial.print(ROVSensor.readEulerPitch()); //Pitch data
    Serial.print("deg ");

		Serial.print(" Temperature: ");
		Serial.print(detectTemperature());
		Serial.print("deg C");

    Serial.print(" A: ");
    Serial.print(ROVSensor.readAccelCalibStatus());  //Accelerometer Calibration Status (0 - 3)

    Serial.print(" M: ");
    Serial.print(ROVSensor.readMagCalibStatus());    //Magnetometer Calibration Status (0 - 3)

    Serial.print(" G: ");
    Serial.print(ROVSensor.readGyroCalibStatus());   //Gyroscope Calibration Status (0 - 3)

    Serial.print(" S: ");
    Serial.print(ROVSensor.readSystemCalibStatus());   //System Calibration Status (0 - 3)

    Serial.println();
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
    go_l = go_l - horizontalSpeedIncrement;
		go_r = go_r - horizontalSpeedIncrement;
		//ESC_LEFT_BACK_VERT.write(stopMotor);
		//ESC_LEFT_FRONT_VERT.write(stopMotor);
		//ESC_RIGHT_BACK_VERT(stopMotor);
		//ESC_RIGHT_FRONT_VERT(stopMotor);
		ESC_LEFT_HORIZ.write(go_l);
		ESC_LEFT_HORIZ.write(go_r);
	} else {
		go_l = 78; // CALIBRATE!!!
		go_r = 81; // TODO
		//ESC_LEFT_BACK_VERT.write(stopMotor);
		//ESC_LEFT_FRONT_VERT.write(stopMotor);
		//ESC_RIGHT_BACK_VERT(stopMotor);
		//ESC_RIGHT_FRONT_VERT(stopMotor);
		ESC_LEFT_HORIZ.write(go_l);
		ESC_LEFT_HORIZ.write(go_r);
		state = 's';
	}

}

void descend() {
	if (state == 'k') {
    ESC_RIGHT_FRONT_VERT.write(115);
		ESC_LEFT_FRONT_VERT.write(115);
		ESC_RIGHT_BACK_VERT.write(115);
		ESC_LEFT_BACK_VERT.write(115);
		ESC_RIGHT_HORIZ.write(stopMotor);
		ESC_LEFT_HORIZ.write(stopMotor);
	} else {
		ESC_RIGHT_FRONT_VERT.write(105);
		ESC_LEFT_FRONT_VERT.write(105);
		ESC_RIGHT_BACK_VERT.write(105);
		ESC_LEFT_BACK_VERT.write(105);
		ESC_RIGHT_HORIZ.write(stopMotor);
		ESC_LEFT_HORIZ.write(stopMotor);
		state = 'k';
	}

}

void ascend() {
	if (state == 'a') {
		ESC_LEFT_FRONT_VERT.write(73);
    ESC_RIGHT_FRONT_VERT.write(70);
    ESC_LEFT_BACK_VERT.write(72);
    ESC_RIGHT_BACK_VERT.write(73);
    ESC_LEFT_HORIZ.write(stopMotor);
    ESC_RIGHT_HORIZ.write(stopMotor);
	} else {
		ESC_LEFT_FRONT_VERT.write(83);
    ESC_RIGHT_FRONT_VERT.write(80);
    ESC_LEFT_BACK_VERT.write(82);
    ESC_RIGHT_BACK_VERT.write(83);
    ESC_LEFT_HORIZ.write(stopMotor);
    ESC_RIGHT_HORIZ.write(stopMotor);
    state = 'a';
	}

}

void turnLeft() {
	if (state == 'a') {
    ESC_LEFT_HORIZ.write(82);
    ESC_RIGHT_HORIZ.write(120);
	} else {
    ESC_LEFT_HORIZ.write(82);
    ESC_RIGHT_HORIZ.write(110);
    state= 'l';
	}

}

void turnRight() {
	if (state == 'd') {
    ESC_LEFT_HORIZ.write(120);
    ESC_RIGHT_HORIZ.write(82);
	} else {
		ESC_LEFT_HORIZ.write(110);
    ESC_RIGHT_HORIZ.write(82);
    state= 'd';
	}

}

void tiltUp() {
	ESC_LEFT_HORIZ.write(stopMotor);
  ESC_RIGHT_HORIZ.write(stopMotor);

  ESC_LEFT_FRONT_VERT.write(70);
  ESC_RIGHT_FRONT_VERT.write(70);
  ESC_LEFT_BACK_VERT.write(stopMotor);
  ESC_RIGHT_BACK_VERT.write(stopMotor);

}

void tiltDown() {
	ESC_LEFT_HORIZ.write(stopMotor);
  ESC_RIGHT_HORIZ.write(stopMotor);

  ESC_LEFT_FRONT_VERT.write(115);
  ESC_RIGHT_FRONT_VERT.write(115);
  ESC_LEFT_BACK_VERT.write(stopMotor);
  ESC_RIGHT_BACK_VERT.write(stopMotor);

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
	state=' ';
  go_l=113;
  go_r=113;
  ESC_LEFT_HORIZ.write(stopMotor);
  ESC_RIGHT_HORIZ.write(stopMotor);

  ESC_LEFT_FRONT_VERT.write(stopMotor);
  ESC_RIGHT_FRONT_VERT.write(stopMotor);
  ESC_LEFT_BACK_VERT.write(stopMotor);
  ESC_RIGHT_BACK_VERT.write(stopMotor);

}

void detectWater() {
	waterlevel = analogRead(waterdetectPin);
	if (waterlevel > 400) { // judgement variable for water detection
		digitalWrite(lightPin, HIGH);
		ascend();
		Serial.println("LEAK DETECTED! ABORTING.");
	} else {
		delay(100);
	}

}

void detectTemperature() {
	templevel = analogRead(tempdetectPin);
	return templevel;

}

void detectPH() {


}
