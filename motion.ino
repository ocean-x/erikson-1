#include <Wire.h>
#include <Servo.h>
#include "NAxisMotion.h" // Bridge code between API and Arduino Environment

NAxisMotion ROVSensor;
unsigned long lastStreamTime = 0; //store last steamed time stamp
const int streamPeriod = 40; //stream at 25Hz. period time is inversely proportional to frequency (1000/40)
bool updateSensorData = true;

Servo esc;
const int control = 3;
const int motor = 5;

void setup() {
  Serial.begin(112500);
  I2C.begin();
  ROVSensor.initSensor();
  ROVSensor.setOperationMode(0x0C); // 9 Degrees of Freedom Sensor Fusion, can be changed to debug
  ROVSensor.setUpdateMode(MANUAL);
  // TODO: below is the configuration of the accelerometer, now need to add the other 2 sensors.
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

  esc.attach(motor);
}




void loop() {
  // TODO: add magnetic data and find a way to meaningfully display on the RPi

  if (updateSensorData)  //Keep the updating of data as a separate task
  {
    ROVSensor.updateAccel();        //Update the Accelerometer data
    ROVSensor.updateLinearAccel();  //Update the Linear Acceleration data
    ROVSensor.updateGravAccel();    //Update the Gravity Acceleration data
    ROVSensor.updateCalibStatus();  //Update the Calibration Status
    updateSensorData = false;
  }

  if ((millis() - lastStreamTime) >= streamPeriod) {

    lastStreamTime = millis();

    Serial.print("Time: ");
    Serial.print(lastStreamTime);
    Serial.print("ms ");

    Serial.print("      aX: ");
    Serial.print(ROVSensor.readAccelX()); //Accelerometer X-Axis data
    Serial.print("m/s2 ");

    Serial.print(" aY: ");
    Serial.print(ROVSensor.readAccelY());  //Accelerometer Y-Axis data
    Serial.print("m/s2 ");

    Serial.print(" aZ: ");
    Serial.print(ROVSensor.readAccelZ());  //Accelerometer Z-Axis data
    Serial.print("m/s2 ");

    Serial.print("      lX: ");
    Serial.print(ROVSensor.readLinearAccelX()); //Linear Acceleration X-Axis data
    Serial.print("m/s2 ");

    Serial.print(" lY: ");
    Serial.print(ROVSensor.readLinearAccelY());  //Linear Acceleration Y-Axis data
    Serial.print("m/s2 ");

    Serial.print(" lZ: ");
    Serial.print(ROVSensor.readLinearAccelZ());  //Linear Acceleration Z-Axis data
    Serial.print("m/s2 ");

    Serial.print("      gX: ");
    Serial.print(ROVSensor.readGravAccelX()); //Gravity Acceleration X-Axis data
    Serial.print("m/s2 ");

    Serial.print(" gY: ");
    Serial.print(ROVSensor.readGravAccelY());  //Gravity Acceleration Y-Axis data
    Serial.print("m/s2 ");

    Serial.print(" gZ: ");
    Serial.print(ROVSensor.readGravAccelZ());  //Gravity Acceleration Z-Axis data
    Serial.print("m/s2 ");

    Serial.print("      C: ");
    Serial.print(ROVSensor.readAccelCalibStatus());  //Accelerometer Calibration Status (0 - 3)

    Serial.println();

    updateSensorData = true;
  }

  int throttle = analogRead(control);
  throttle = map(throttle, 0, 1023, 0, 179);
  esc.write(throttle);

}
