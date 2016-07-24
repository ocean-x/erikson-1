## Procedure (why do we want to build one instead of buying one??)
Our motivation to create an ROV was to ensure customisability and robustness for observation and data collection. 

### Sensors
For now, the ROV can collect data of water temperature and pH level.

The ROV has a temperature and pH sensor to quantitatively measure the two variables that seem to affect algal bloom. However, the ROV can be outfitted with a variety of different sensors depending on the required application. 

### Datalogger
The datalogger is linked to the sensors and will plot a graph to detect trends of the pH level and temperature of its surroundings. 

### PVC Housing
The housing of the submarine was intended to contain all electrical components that control the submarine and relay the information to the surface computer and had to be designed to be stiff. The selection for the housing was a hard PVC tube of 10cm inner diameter, 12.5cm outer diameter, and 50cm in length. Hard PVC has a maximum tensile stress of 5003.8 psi before failure, which was deemed as acceptable for our limited application. 

[Material properties of pvc hard, commodity polymers. In (2009). MATBASE. Retrieved from].

### Acrylic Flanges
The flanges of the submarine are made of acrylic sheets and are used as a surface for attaching thrusters and fastening the housing.

### Acrylic Rods
The 5-inch acrylic rods are used to fix the acrylic flanges on the sides of the housing to the housing by screwing it into the acrylic flanges

### Lithium Polymer Battery
There are power requirements to be met. A battery 
or batteries must be sufficient for motor control 
and the core computing devices. In the case there 
is mains electricity nearby, we cannot discount the 
possibility that we just attach a 12V/3A breakout to 
power the setup.

We chose a lithium polymer battery because of its high charge density; our two batteries can provide 2500mAh per cycle. We decided against NiCad and lead-acid batteries due to potential toxicity and low current output that is not suitable for powering our motors. 

### Arduino Mega 2560
The Arduino will execute the code to operate the 6 motors.
The Arduino provides a low-level C runtime to control the 6 motors. There is a wide range of shields and compatible sensors for this platform, and it can be scaled up to communicate with an onboard computer such as a Raspberry Pi for future navigation and observation, which include a camera and GPS. 

### Motors
We chose brushless direct current (BLDC) motors for a few reasons. Firstly, carbon brushes wear out over time, and eliminating the brushes would make the ROV’s operation more reliable. Secondly, carbon brushes would short underwater, the use of a spinning magnetic field to drive a BLDC means that it can function in an aquatic medium without waterproofing. 




