#include <Wire.h>
#include <HMC5883L.h>

HMC5883L compass;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  compass = HMC5883L; //new instance of compass library
  setupHMC5883L(); //setup the HMC5883L
}

void loop() {
  float heading = getHeading();
  Serial.println(heading);
  delay(100); //only here to slow down the serial print
}

void setupHMC5883L() {
  int error;
  error = compass.setScale(1.3); //set the scale of the compass
  if (error != 0) {
    Serial.println(compass.GetErrorText(error));
  }
  error = compass.SetMeasurementMode(Measurement_Continuous);
  if (error != 0) {
    Serial.println(compass.GetErrorText(error))
  }
}

float getHeading() {
  MagnetometerScaled scaled = compass.ReadScaledAxis();
  float heading = atan2(scaled.YAxis, scaled.XAxis);

  if (heading < 0) heading += 2*PI;
  if (heading > 2*PI) heading -= 2*PI;

  return heading * RAD_TO_DEG;
}
