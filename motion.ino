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
  ROVSensor.initSensor();
  ROVSensor.setOperationMode(0x0C); // 9 Degrees of Freedom Sensor Fusion, can be changed to debug
  ROVSensor.setUpdateMode(MANUAL);
  // TODO: below is the configuration of the accelerometer, now need to add the other 2 sensors.
  ROVSensor.updateAccelConfig();
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
  if (updateSensorData)  //Keep the updating of data as a separate task
  {
    mySensor.updateAccel();        //Update the Accelerometer data
    mySensor.updateLinearAccel();  //Update the Linear Acceleration data
    mySensor.updateGravAccel();    //Update the Gravity Acceleration data
    mySensor.updateCalibStatus();  //Update the Calibration Status
    updateSensorData = false;
  }
  
  if ((millis() - lastStreamTime) >= streamPeriod) {

    lastStreamTime = millis();

    Serial.print("Time: ");
    Serial.print(lastStreamTime);
    Serial.print("ms ");

    Serial.print("      aX: ");
    Serial.print(mySensor.readAccelX()); //Accelerometer X-Axis data
    Serial.print("m/s2 ");

    Serial.print(" aY: ");
    Serial.print(mySensor.readAccelY());  //Accelerometer Y-Axis data
    Serial.print("m/s2 ");

    Serial.print(" aZ: ");
    Serial.print(mySensor.readAccelZ());  //Accelerometer Z-Axis data
    Serial.print("m/s2 ");

    Serial.print("      lX: ");
    Serial.print(mySensor.readLinearAccelX()); //Linear Acceleration X-Axis data
    Serial.print("m/s2 ");

    Serial.print(" lY: ");
    Serial.print(mySensor.readLinearAccelY());  //Linear Acceleration Y-Axis data
    Serial.print("m/s2 ");

    Serial.print(" lZ: ");
    Serial.print(mySensor.readLinearAccelZ());  //Linear Acceleration Z-Axis data
    Serial.print("m/s2 ");

    Serial.print("      gX: ");
    Serial.print(mySensor.readGravAccelX()); //Gravity Acceleration X-Axis data
    Serial.print("m/s2 ");

    Serial.print(" gY: ");
    Serial.print(mySensor.readGravAccelY());  //Gravity Acceleration Y-Axis data
    Serial.print("m/s2 ");

    Serial.print(" gZ: ");
    Serial.print(mySensor.readGravAccelZ());  //Gravity Acceleration Z-Axis data
    Serial.print("m/s2 ");

    Serial.print("      C: ");
    Serial.print(mySensor.readAccelCalibStatus());  //Accelerometer Calibration Status (0 - 3)

    Serial.println();

    updateSensorData = true;
  }

}
