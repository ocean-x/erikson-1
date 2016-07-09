#include <Servo.h>
Servo esc;
const int motors[] = {9, 10, 11};
const int controls[] = {0, 1, 2};

void setup() {
  esc.attach(9);
}

void loop() {
  int throttle = analogRead(throttlePin);
  throttle = map(throttle, 0, 1023, 0, 179);
  esc.write(throttle);
}
  
