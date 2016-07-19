#include <Servo.h>

const int controllerInputPin = 5;
const int controllerOutputPin = 9;
int controllerInput;
int controllerOutput;

Servo servo

void setup() {
  pinMode(controllerOutputPin, OUTPUT);
  Serial.begin(9600);

  servo.attach(controllerOutputPin);

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
  servo.writeMicroseconds(controllerOutput);
}
