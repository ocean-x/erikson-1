#include <Wire.h>
#include <Servo.h>
#include "NAxisMotion.h" // Bridge code between API and Arduino Environment

void setup() {
  Serial.begin(112500);
  I2C.begin();
  mySensor.initSensor();
  mySensor.setOperationMode(OPERATION_MODE_NDOF);

}

void loop() {

}
