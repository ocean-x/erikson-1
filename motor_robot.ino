int keyValue[5] = {0, 50, 100, 140, 550}; //actual values are closer, but rounded to nearest 10.
int NUM_KEYS = 5;
int keyInput;
int key =- 1;
int oldkey =- 1;

void setup() {
  pinMode(13, OUTPUT); // This is an indicator of a button press.
  Serial.begin(9600);
}

void loop() {
  keyInput = analogRead(A0);
  digitalWrite(13, LOW);
  //Serial.println(keyInput); // Prints the value, erase later, for debugging

  key = getKey(keyInput); // record keypress

  if (key != oldkey) {     //if keypress is detected
    delay(50);
    keyInput = analogRead(A0);
    key = getKey(keyInput); //convert into keypress
    if (key != oldkey) {
      oldkey = key;
      if (key >= 0) {
        digitalWrite(13, HIGH);
        switch(key) {
          case 0 : Serial.println("STOP BUTTON PRESSED");
          break;
          case 1 : Serial.println("RESET BUTTON PRESSED");
          break;
          case 2 : Serial.println("LEFT BUTTON PRESSED");
          break;
          case 3 : Serial.println("FORWARD BUTTON PRESSED");
          break;
          case 4 : Serial.println("RIGHT BUTTON PRESSED");
          break;
        }
      }
    }
    delay(100);
  }
}

// Converts keyInput value to key number
int getKey(unsigned int input)
  {
      int k;
      for (k = 0; k < NUM_KEYS; k++)
      {
        if (input <= keyValue[k])
       {
              return k;
          }
     }
         if (k >= NUM_KEYS)k = -1;  // No valid key pressed
         return k;
  }
