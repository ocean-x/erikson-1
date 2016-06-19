#include <Wire.h>
#include <Servo.h>
#define BACKLIGHT_PIN     3
#define ROTATION_SPEED 150
#define DEFAULT_SPEED 150
int keyValue[5] = {20, 55, 100, 200, 600}; //actual values are closer, but rounded to nearest 10.
int NUM_KEYS = 5;
int keyInput;
int key =- 1;
int oldkey =- 1;
int targetArray[8] = {1,1,2,1,3,1,2,1};
int pathArray[8] = {0,0,0,0,0,0,0,0};
int j = 0; // path counter
const int MOTOR_RIGHT_IN1 = 2;
const int MOTOR_RIGHT_IN2 = 3;
const int MOTOR_LEFT_IN3 = 4;
const int MOTOR_LEFT_IN4 = 5;
bool pass = false; // initial pass condition is false.

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, BACKLIGHT_PIN, POSITIVE);  // Set the LCD I2C address
void setup()
{
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode ( BACKLIGHT_PIN, OUTPUT );
  digitalWrite ( BACKLIGHT_PIN, HIGH );
  lcd.begin(16,2);
  lcd.home();
  lcd.print("Hello, ARDUINO ");
  lcd.setCursor( 0, 1 );
  lcd.print ("This is an LCD");
  robotStop();
  delay(500);
  robotBack();
  delay(2000);
  robotStop();
  //int angle = sweepForBestAngle();
  //angle = angle - 90;
  robotRotateLeft(90);
  robotForward();
}

void loop() {
  if (pathArray[7] != 0 && pathArray[7] == 2 || pathArray[7] == 3) {
    Serial.println("You've ran out of spaces!"); //player has ran out of possible moves
  }
  digitalWrite(13, LOW);
  keyInput = analogRead(0);
  //Serial.println(keyInput); // Prints the value, erase later, for debugging
​
  key = getKey(keyInput); // record keypress
​
  if (key != oldkey) {     //if keypress is detected
    delay(50);
    keyInput = analogRead(0);
    key = getKey(keyInput); //convert into keypress
    if (key != oldkey) {
      oldkey = key;
      if (key >= 0) {
        tone(10, 4000, 200);
        digitalWrite(13, HIGH);
        switch(key) {
          case 0 : Serial.println("ENTER BUTTON PRESSED");
                   pass = check();
                   tone(10, 4000, 200);
                   if(pass==true) move();
          break;
          case 1 : Serial.println("RESET BUTTON PRESSED");
                   int k;
                   for (k = 0; k < 8; k++) {
                     pathArray[k] = 0;
                   }
                   j = 0;
                   tone(10, 4000, 200);
          break;
          case 2 : Serial.println("LEFT BUTTON PRESSED");
                   pathArray[j] = 2;
                   j++;
                   tone(10, 4000, 200);
          break;
          case 3 : Serial.println("FORWARD BUTTON PRESSED");
                   pathArray[j] = 1;
                   j++;
                   tone(10, 4000, 200);
          break;
          case 4 : Serial.println("RIGHT BUTTON PRESSED");
                   pathArray[j] = 3;
                   j++;
                   tone(10, 4000, 200);
          break;
          }
​
        }
      }
    }
  }
}​
void move() {
  for(int i=0;i<targetArray.length;i++) {
    if(targetArray[i] == 1) robotForward();
    else if(targetArray[i] == 2) robotRotateLeft();
    else if(targetArray[i] == 3) robotRotateRight();
  }
}
​


/**************************************************/
// Don't change the code below unless
// you know what you're doing :)
/**************************************************/
int sweepForBestAngle() {
  int pos;
  int bestDistance = 0;
  int bestAngle = 0;

  // Move to starting position
  distanceServo.write(0);
  delay(240);
  for(pos = 0; pos <= 180; pos += 30) {
    distanceServo.write(pos);
    delay(300);
    int distance = sonar.ping_cm();
    if (distance == 0) {
      distance = MAX_DISTANCE;
    }
    if (distance > bestDistance) {
      bestAngle = pos;
      bestDistance = distance;
    }
  }

  distanceServo.write(bestAngle);
  delay(240);
}
void robotRotateLeft() {
  digitalWrite(MOTOR_RIGHT_IN1, HIGH);
  analogWrite(MOTOR_RIGHT_IN2, 255 - ROTATION_SPEED);
  digitalWrite(MOTOR_LEFT_IN3, LOW);
  analogWrite(MOTOR_LEFT_IN4, ROTATION_SPEED);
}
void robotRotateLeft(int angle) {
  if (angle < 0) {
    robotRotateRight();
    angle = -angle;
  } else {
    robotRotateLeft();
  }
  delay(angle*4);
  robotStop();
}
void robotRotateRight() {
  digitalWrite(MOTOR_RIGHT_IN1, LOW);
  analogWrite(MOTOR_RIGHT_IN2, ROTATION_SPEED);
  digitalWrite(MOTOR_LEFT_IN3, HIGH);
  analogWrite(MOTOR_LEFT_IN4, 255 - ROTATION_SPEED);
}
void robotRotateRight(int angle) {
  if (angle < 0) {
    robotRotateRight();
    angle = -angle;
  } else {
    robotRotateLeft();
  }
  delay(angle*4);
  robotStop();
}
void robotForward() {
  robotForward(DEFAULT_SPEED);
}
void robotBack() {
  robotForward(-DEFAULT_SPEED);
}
void robotForward(int speed) {
  speed = constrain(speed, -255, 255);
  if (speed == 0) {
    robotStop();
  } else if (speed > 0) {
    // Move forward
    digitalWrite(MOTOR_RIGHT_IN1, HIGH);
    analogWrite(MOTOR_RIGHT_IN2, 255 - speed);
    digitalWrite(MOTOR_LEFT_IN3, HIGH);
    analogWrite(MOTOR_LEFT_IN4, 255 - speed);
  } else {
    // Move backwards
    digitalWrite(MOTOR_RIGHT_IN1, LOW);
    analogWrite(MOTOR_RIGHT_IN2, -speed);
    digitalWrite(MOTOR_LEFT_IN3, LOW);
    analogWrite(MOTOR_LEFT_IN4, -speed);
  }
}
void robotForward(long duration, int speed) {
  robotForward(speed);
  delay(duration);
  robotStop();
}

void robotStop() {
  digitalWrite(MOTOR_RIGHT_IN1, LOW);
  analogWrite(MOTOR_RIGHT_IN2, LOW);
  digitalWrite(MOTOR_LEFT_IN3, LOW);
  analogWrite(MOTOR_LEFT_IN4, LOW);
}
// Converts keyInput value to key number
int getKey(unsigned int input)
  {
      int k;
      for (k = 0; k < NUM_KEYS; k++)
      {
        if (input < keyValue[k])
       {
              return k;
          }
     }
         if (k >= NUM_KEYS)k = -1;  // No valid key pressed
         return k;
  }
bool check() {
  int k;
  for (k = 0; k <8; k++) {
    if (targetArray[k] != pathArray[k]) {
      Serial.println("You've got it wrong, try again?");
      return false;
    }
  }
  Serial.println("Yay! Congratulations, the clue to your next puzzle is: ");
  return true;
}
/*
1. code LCD (everything is still in serial)
2. drive the motors (because this is still a screen puzzle, nothing moves)
3. build the fucking robot (but athena is overseas)
*/
