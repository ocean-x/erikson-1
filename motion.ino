#include <Wire.h>
#include <Servo.h>
#include "NAxisMotion.h" // Bridge code between API and Arduino Environment

NAxisMotion ROVSensor;
unsigned long lastStreamTime = 0; //store last steamed time stamp
const int streamPeriod = 40; //stream at 25Hz. period time is inversely proportional to frequency (1000/40)
bool upDateSensorData = true;

void setup() {
  Serial.begin(112500);
  I2C.begin();
  mySensor.initSensor();
  mySensor.setOperationMode(0x0C); // 9 Degrees of Freedom Sensor Fusion, can be changed to debug
  mySensor.setUpdateMode(MANUAL);
  // TODO: below is the configuration of the accelerometer, now need to add the other 2 sensors. 
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
}


}

void loop() {

}
