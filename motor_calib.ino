/*
OCEANX MOTOR CALIBRATION SYSTEM –
Tested with Arduino Mega 2560

Turn on the serial monitor for this to work

The PWM signal read by an ESC is the same as a servo signal.
So we can use the servo library to make it work.
The default signal range for most servos and ESCs is a high signal width between 1000 and 2000
microseconds. 

TODO: Calibrate ESCs

*/

#include <Servo.h>

#define MAX_SIGNAL 2000
#define MIN_SIGNAL 1000
#define MOTOR_PIN 9

Servo motor;

void setup() {
  Serial.begin(9600);
	Serial.println("This program will calibrate the ESC");

	motor.attach(MOTOR_PIN);

	Serial.println("Now writing maximum output");
	Serial.println("Turn on power source, wait for 2 seconds and press any key");
	motor.writeMicroseconds(MAX_SIGNAL);

	while (!Serial.available()) {
		Serial.read();
	}

	Serial.println("Sending minimum output");
	motor.writeMicroseconds(MIN_SIGNAL);
}

void loop() {

}
