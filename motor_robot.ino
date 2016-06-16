void setup() {
  // put your setup code here, to run once:
  int movement[]{};
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  int reading = analogRead(A0);
  Serial.println(reading);
  delay(50);


}
