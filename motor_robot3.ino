int keyValue[5] = {0, 50, 100, 140, 550}; //actual values are closer, but rounded to nearest 10.
int NUM_KEYS = 5;
int keyInput;
int key =- 1;
int oldkey =- 1;
int targetArray[8] = {1,1,2,1,3,1,2,1};
int pathArray[8] = {0,0,0,0,0,0,0,0};
int j = 0; // path counter
bool pass = false; // initial pass condition is false.

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
}

void loop() {
  if(pathArray[7] != 0) {
    Serial.println("You've ran out of spaces!"); //player has ran out of possible moves
  }
  digitalWrite(13, LOW);
  keyInput = analogRead(0);
  //Serial.println(keyInput); // Prints the value, erase later, for debugging

  key = getKey(keyInput); // record keypress

  if (key != oldkey) {     //if keypress is detected
    delay(50);
    keyInput = analogRead(0);
    key = getKey(keyInput); //convert into keypress
    if (key != oldkey) {
      oldkey = key;
      if (key >= 0) {
        digitalWrite(13, HIGH);
        switch(key) {
          case 0 : Serial.println("ENTER BUTTON PRESSED");
          break;
          case 1 : Serial.println("RESET BUTTON PRESSED");
          break;
          case 2 : Serial.println("LEFT BUTTON PRESSED");
          pathArray[j] = 2;
          break;
          case 3 : Serial.println("FORWARD BUTTON PRESSED");
          pathArray[j] = 1;
          break;
          case 4 : Serial.println("RIGHT BUTTON PRESSED");
          pathArray[j] = 3;
          break;
          }
          j++;
        }
      }
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
