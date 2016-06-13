const int controls[] = {14, 15, 16};
const int motors[] = {6, 9, 5, 3, 2, 4};

void setup() {
  for (int a = 0; a < 3; ++a)
    pinMode(controls[a], INPUT);
  for (int a = 0; a < 6; ++a)
    pinMode(motors[a], OUTPUT);
}

void loop() {
  int input[3], output[6] = {0};
  for (int a = 0; a < 3; ++a)
    input[a] = analogRead(controls[a]); // [UD, FB, LR] (analog input)
  /* 512 = Neutral Value, change as needed */
  /* UD */
  if (input[0] != 512) { // Reverse - 512 - Forward
    (input[0] > 512 ? output[0] : output[1]) = map(input[0], 0, 1023, 0, 255); // Center Motor
  }
  /* FB (Higher priority) */
  if (input[1] != 512) { // Reverse - 512 - Forward
    (input[1] > 512 ? output[2] : output[3]) = map(input[1], 0, 1023, 0, 255); // Left Motor
    (input[1] > 512 ? output[4] : output[5]) = map(input[1], 0, 1023, 0, 255); // Right Motor
  }
  /* LR (Lower priority) */
  else if (input[2] != 512) { // Left - 512 - Right
    (input[2] > 512 ? output[3] : output[2]) = map(input[2], 0, 1023, 0, 255); // Left Motor
    (input[2] > 512 ? output[4] : output[5]) = map(input[2], 0, 1023, 0, 255); // Right Motor
  }
  for (int a = 0; a < 6; ++a)
    analogWrite(motors[a], output[a]); // Center[2], Left[2], Right[2]
  // Assuming [x, 0] for forward, [0, x] for reverse by a magnitude of x
}
