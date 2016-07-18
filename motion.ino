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

/****************************************************************************
* Copyright (C) 2011 - 2014 Bosch Sensortec GmbH
*
* Euler.ino
* Date: 2014/09/09
* Revision: 3.0 $
*
* Usage:        Example code to stream Euler data
*
****************************************************************************
/***************************************************************************
* License:
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
*   Redistributions of source code must retain the above copyright
*   notice, this list of conditions and the following disclaimer.
*
*   Redistributions in binary form must reproduce the above copyright
*   notice, this list of conditions and the following disclaimer in the
*   documentation and/or other materials provided with the distribution.
*
*   Neither the name of the copyright holder nor the names of the
*   contributors may be used to endorse or promote products derived from
*   this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY
* DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE
*
* The information provided is believed to be accurate and reliable.
* The copyright holder assumes no responsibility for the consequences of use
* of such information nor for any infringement of patents or
* other rights of third parties which may result from its use.
* No license is granted by implication or otherwise under any patent or
* patent rights of the copyright holder.
*/

#include <NAxisMotion.h>       //Contains the bridge code between the API and the Arduino Environment
#include <Wire.h>

NAxisMotion mySensor;         //Object that for the sensor
unsigned long lastStreamTime = 0;     //To store the last streamed time stamp
const int streamPeriod = 20;          //To stream at 50Hz without using additional timers (time period(ms) =1000/frequency(Hz))

void setup() //This code is executed once
{
  //Peripheral Initialization
  Serial.begin(115200);           //Initialize the Serial Port to view information on the Serial Monitor
  I2C.begin();                    //Initialize I2C communication to the let the library communicate with the sensor.
  //Sensor Initialization
  mySensor.initSensor();          //The I2C Address can be changed here inside this function in the library
  mySensor.setOperationMode(OPERATION_MODE_NDOF);   //Can be configured to other operation modes as desired
  mySensor.setUpdateMode(MANUAL);	//The default is AUTO. Changing to MANUAL requires calling the relevant update functions prior to calling the read functions
  //Setting to MANUAL requires fewer reads to the sensor
  Serial.println("Streaming in ...");	//Countdown
  Serial.print("3...");
  delay(1000);	//Wait for a second
  Serial.print("2...");
  delay(1000);	//Wait for a second
  Serial.println("1...");
  delay(1000);	//Wait for a second
}

void loop() //This code is looped forever
{
  if ((millis() - lastStreamTime) >= streamPeriod)
  {
    lastStreamTime = millis();
    mySensor.updateEuler();        //Update the Euler data into the structure of the object
    mySensor.updateCalibStatus();  //Update the Calibration Status

    Serial.print("Time: ");
    Serial.print(lastStreamTime);
    Serial.print("ms ");

    Serial.print(" Yaw: ");
    Serial.print(mySensor.readEulerHeading()); //Heading data
    Serial.print("deg ");

    Serial.print(" Roll: ");
    Serial.print(mySensor.readEulerRoll()); //Roll data
    Serial.print("deg");

    Serial.print(" Pitch: ");
    Serial.print(mySensor.readEulerPitch()); //Pitch data
    Serial.print("deg ");

    Serial.print(" A: ");
    Serial.print(mySensor.readAccelCalibStatus());  //Accelerometer Calibration Status (0 - 3)

    Serial.print(" M: ");
    Serial.print(mySensor.readMagCalibStatus());    //Magnetometer Calibration Status (0 - 3)

    Serial.print(" G: ");
    Serial.print(mySensor.readGyroCalibStatus());   //Gyroscope Calibration Status (0 - 3)

    Serial.print(" S: ");
    Serial.print(mySensor.readSystemCalibStatus());   //System Calibration Status (0 - 3)

    Serial.println();
  }
}
