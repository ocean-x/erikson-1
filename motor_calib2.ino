#include <Servo.h>

const int controllerInputPin = 5;
const int rightMotorPin = 9;
const int leftMotorPin = 10;
const int verticaloneMotorPin = 7;
const int verticaltwoMotorPin = 6;
const int verticalthreeMotorPin = 2;
const int verticalfourMotorPin = 3;

int controllerInput;
int controllerOutput;

Servo rightMotor;
Servo leftMotor;
Servo verticaloneMotor;
Servo verticaltwoMotor;
Servo verticalthreeMotor;
Servo verticalfourMotor;

void setup() {
  pinMode(rightMotorPin, OUTPUT);
  pinMode(leftMotorPin, OUTPUT);
  pinMode(verticaloneMotorPin, OUTPUT);
  pinMode(verticaltwoMotorPin, OUTPUT);
  pinMode(verticalfourMotorPin, OUTPUT);
  pinMode(verticalthreeMotorPin, OUTPUT);

  Serial.begin(9600);

  rightMotor.attach(rightMotorPin);
  leftMotor.attach(leftMotorPin);
  verticaloneMotor.attach(verticaloneMotorPin);
  verticaltwoMotor.attach(verticaltwoMotorPin);
  verticalthreeMotor.attach(verticalthreeMotorPin);
  verticalfourMotor.attach(verticalfourMotorPin);


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
  verticaloneMotor.write(verticaloneMotorPin);
  verticaltwoMotor.write(verticaltwoMotorPin);
  verticalthreeMotor.write(verticalthreeMotorPin);
  verticalfourMotor.write(verticalfourMotorPin);
}
