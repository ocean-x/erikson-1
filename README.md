# erikson-1
An aquatic remotely-operated vehicle, currently in initial development. 
We began developing and building the first iteration of our ROV at the beginning of June 2016. We intend to present a stable version of the vessel at the Victoria Junior College Science Fair during the same year. 

The repository wiki will be where we record our planning and thoughts throughout the development and building process. 

Our team members include Wayne, Rubesh, Wazir and Ivan. 

## Engineering goals

* Raspberry Pi and Arduino
* Waterproofed main housing
* Six thrusters (2 horizontal, 4 vertical)
* Effective depth of up to 2.4m
* Effective range of up to 15m
* Solid ballasts

This iteration will be controlled by a Raspberry Pi acting as the 'host' computer, with the Arduino acting as the motor controller. The CAT5 tether connecting the ROV to the base station is 15m long. 

Future iterations, will contain a live video, telemetry feed, and safety measures. This will be managed by the Raspberry Pi. Telemetry will include sensors and navigation equipment. Safety measures will include devices which address safety concerns.

### Navigation

* Compass
* Accelerometer
* Gyroscope

### Telemetry

* Video feed
* Temperature
* pH sensor
* Oxygen sensor
* Salinity sensor (possibly)
* Alcohol sensor (possibly)

### Safety Measures

* Chamber pressure sensor - For detection of air leakage through faulty waterproofing mechanisms
* Chamber temperature sensor - For detection of malfunctioning/overheating components due to possible short-circuits.
* Chamber water sensor - For detection of water penetration in the chamber due to a complete failure of water proofing mechanisms.
* Impact sensor - For detection of collisions and hard debris.
* Data connection sensor - For detection of CAT5 disconnection.
* Motion sensor - For detection of unintentional motion due to currents, debris, etc, by utilizing the accelerometer.



We hope that future versions will be able to include more sophisticated technologies such as GPS and fluid ballasts.

If the tether, which provides a variable weight at the rear, is removed, the submarine would have improved movement and stability. The addition of a depth sensor would allow the submarine to descend and hold set depth and avoid constant manual adjustments to hold a constant depth.
