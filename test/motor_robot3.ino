#include <Wire.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#define BACKLIGHT_PIN     13
#define ROTATION_SPEED 150
#define DEFAULT_SPEED 150
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address

int keyValue[5] = {20, 55, 100, 200, 600}; //actual values are closer, but rounded to nearest 10.
int NUM_KEYS = 5;
int keyInput;
int key =- 1;
int oldkey =- 1;
int targetArray[8] = {1,1,2,1,3,1,2,1};
int pathArray[8] = {0,0,0,0,0,0,0,0};
int j = 0; // path counter
const int MOTOR_RIGHT_IN1 = 7;
const int MOTOR_RIGHT_IN2 = 8;
const int MOTOR_LEFT_IN3 = 9;
const int MOTOR_LEFT_IN4 = 10;

const int ULTRASONIC_TRIGGER = 6;
const int ULTRASONIC_ECHO = 5;
const int SERVO_PIN = 4;

const int LIMIT_SWITCH_LEFT = 11;
const int LIMIT_SWITCH_RIGHT = 12;

Servo distanceServo;
bool pass = false; // initial pass condition is false.

void setup() {
  // Switch on the backlight
  pinMode ( BACKLIGHT_PIN, OUTPUT );
  digitalWrite ( BACKLIGHT_PIN, HIGH );

  pinMode(SERVO_PIN, OUTPUT); // so the damn thing can run around
  pinMode(ULTRASONIC_TRIGGER, OUTPUT);
  pinMode(ULTRASONIC_ECHO, INPUT);

  lcd.begin(16,2);
  lcd.home ();
  lcd.print("Hello, PLAYER 1");
  lcd.setCursor (0,1);
  lcd.print ("This is a puzzle");

  Serial.begin(9600);
  pinMode(13, OUTPUT);
  distanceServo.attach(SERVO_PIN);
}

void loop() {
  int left_bumper = digitalRead(LIMIT_SWITCH_LEFT);
  int right_bumper = digitalRead(LIMIT_SWITCH_RIGHT);
  move();
  if (pathArray[7] != 0 && pathArray[7] == 2 || pathArray[7] == 3) {
    Serial.println("You're out of spaces!"); //player has ran out of possible moves
    lcd.clear();
    lcd.print("Out of spaces!");
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
        tone(10, 4000, 200);
        digitalWrite(13, HIGH);
        switch(key) {
          case 0 : Serial.println("ENTER BUTTON PRESSED");
                   pass = check();
                   tone(10, 4000, 200);

          break;
          case 1 : Serial.println("RESET BUTTON PRESSED");
                   int k;
                   for (k = 0; k < 8; k++) {
                     pathArray[k] = 0;
                   }
                   j = 0;
                   tone(10, 4000, 200);
                   lcd.clear();
                   lcd.print("RESET");
                   lcd.setCursor (0,1);
                   lcd.print ("This is a puzzle");
          break;
          case 2 : Serial.println("LEFT BUTTON PRESSED");
                   pathArray[j] = 2;
                   j++;
                   tone(10, 4000, 200);
                   lcd.clear();
                   lcd.print("LEFT");
          break;
          case 3 : Serial.println("FORWARD BUTTON PRESSED");
                   pathArray[j] = 1;
                   j++;
                   tone(10, 4000, 200);
                   lcd.clear();
                   lcd.print("FORWARD");
          break;
          case 4 : Serial.println("RIGHT BUTTON PRESSED");
                   pathArray[j] = 3;
                   j++;
                   tone(10, 4000, 200);
                   lcd.clear();
                   lcd.print("RIGHT");
          break;
          }

        }
      }
    }
  }

void move() {
  if (left_bumper || right_bumper) {
    robotStop();
    delay(500);
    robotBack();
    delay(2000);
    robotStop();
    int angle = sweepForBestAngle();
    angle = angle - 90;
    robotRotateLeft(angle);
    robotForward();
  }
  /*for(int i=0;i<8;i++) {
    if(targetArray[i] == 1) robotForward();
    else if(targetArray[i] == 2) robotRotateLeft();
    else if(targetArray[i] == 3) robotRotateRight();

  }
  */
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
      lcd.clear();
      lcd.print("WRONG, TRY AGAIN?");
      lcd.setCursor (0,1);
      lcd.print ("PRESS RESET");
      return false;
      delay(2000);
    }
  }
  Serial.println("Yay! Congratulations, the clue to your next puzzle is: ");
  lcd.clear();
  lcd.print("CONGRATULATIONS!");
  lcd.setCursor (0,1);
  lcd.print ("NEXT CODE: 1234");
  return true;
  delay(2000);
}

/*
1. code LCD (everything is still in serial)
2. drive the motors (because this is still a screen puzzle, nothing moves)
3. build the fucking robot (but athena is overseas)
*/

/**************************************************/
// Don't change the code below unless
// you know what you're doing :)
// Angle sweep is when you have the ultrasonic sensor and servo
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
  // Stop
  digitalWrite(MOTOR_RIGHT_IN1, LOW);
  analogWrite(MOTOR_RIGHT_IN2, LOW);
  digitalWrite(MOTOR_LEFT_IN3, LOW);
  analogWrite(MOTOR_LEFT_IN4, LOW);
}
