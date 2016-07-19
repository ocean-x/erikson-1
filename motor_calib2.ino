#include <Servo.h>

const int controllerInputPin = 5;
const int rightMotorPin = 9;
const int leftMotorPin = 10;
const int centerMotorPin = 11;
int controllerInput;
int controllerOutput;

Servo rightMotor;
Servo leftMotor;
Servo centerMotor;

void setup() {
  pinMode(rightMotorPin, OUTPUT);
  pinMode(leftMotorPin, OUTPUT);
  Serial.begin(9600);

  rightMotor.attach(rightMotorPin);
  leftMotor.attach(leftMotorPin);
  centerMotor.attach(centerMotorPin);

}

void loop() {
  controllerInput = analogRead(controllerInputPin);
  controllerOutput = map(controllerInput, 0, 1023, 700, 2000);


  Serial.print("Input Signal: ");
  Serial.print(controllerInput);
  Serial.print(" ");
  Serial.print("Output Signal: ");
  Serial.print(controllerOutput);
  Serial.print(" ");
  Serial.println();
  rightMotor.write(controllerOutput);
  leftMotor.write(controllerOutput);
  centerMotor.write(controllerOutput);
}
