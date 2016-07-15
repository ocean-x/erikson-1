const int bluePin = 5;
const int greenPin = 6;
const int redPin = 9;

void setup() {
  pinMode(bluePin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(redPin, OUTPUT);
}

void loop() {
  analogWrite(redPin, 255);
  analogWrite(bluePin, 0);
  analogWrite(greenPin, 0);
}
