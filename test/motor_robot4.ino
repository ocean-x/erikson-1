#include <NewPing.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#define BACKLIGHT_PIN     13
#define ROTATION_SPEED 150
#define DEFAULT_SPEED 150
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address

int keyValue[5] = {20, 55, 100, 200, 600}; //actual values are closer, but rounded to nearest 10.
int NUM_KEYS = 5;
int keyInput;
int key = - 1;
int oldkey = - 1;
int targetArray[5] = {3, 1, 2, 5, 4};
int pathArray[5] = {0, 0, 0, 0, 0};
int j = 0; // path counter
const int MOTOR_RIGHT_IN1 = 7;
const int MOTOR_RIGHT_IN2 = 8;
const int MOTOR_LEFT_IN3 = 9;
const int MOTOR_LEFT_IN4 = 10;
int buzzer = 11;

int mario[] = {1319, 1568, 2637, 2093, 2349, 3136};

int one[5] = {200, 500, 500, 500, 500};
int two[5] = {200, 200, 500, 500, 500};
int three[5] = {200, 200, 200, 500, 500};
int four[5] = {200, 200, 200, 200, 500};
int five[5] = {200, 200, 200, 200, 200};

NewPing sonar(3, 4, 200);
bool beep = false;

void setup() {
  // Switch on the backlight
  pinMode ( BACKLIGHT_PIN, OUTPUT );
  digitalWrite ( BACKLIGHT_PIN, HIGH );

  lcd.begin(16, 2);
  lcd.home ();
  lcd.print("PUT ME IN CENTER");
  lcd.setCursor (0, 1);
  lcd.print ("THEN PRESS A KEY");

  Serial.begin(9600);
  while (analogRead(0) > 1000) {
    continue;
  }
  digitalWrite(MOTOR_RIGHT_IN1, HIGH);
  analogWrite(MOTOR_RIGHT_IN2, 10);
  digitalWrite(MOTOR_LEFT_IN3, HIGH);
  analogWrite(MOTOR_LEFT_IN4, 75);
  Serial.println("hi");
}

void morse(int a[5]) {
  for (int i = 0; i < 5; i++) {
    Serial.println(sonar.ping());
    int d = sonar.ping() / US_ROUNDTRIP_CM;
    Serial.println(d);
    if (d > 5) {
      beep = true;
      lcd.clear();
      lcd.print("COLIN V8.0");
      lcd.setCursor(0,1);
      lcd.print("INPUT PIN:");
      return;
    } else {
      tone(buzzer, 523, a[i]);
      delay(200 + a[i]);
    }
  }
}
void loop() {



  check();
Serial.println("hi2");

  keyInput = analogRead(0);
  //Serial.println(keyInput); // Prints the value, erase later, for debugging

  key = getKey(keyInput); // record keypress

  if (key != oldkey && beep) {     //if keypress is detected
    delay(50);
    keyInput = analogRead(0);
    key = getKey(keyInput); //convert into keypress
    if (key != oldkey) {
      oldkey = key;
      if (key >= 0) {
        switch (key) {
          case 0 : pathArray[j] = 1;
            lcd.print(1);
            j++;
            break;
          case 1 : pathArray[j] = 5;
            lcd.print(5);
            j++;
            break;
          case 2 : pathArray[j] = 2;
            lcd.print(2);
            j++;
            break;
          case 3 : pathArray[j] = 3;
            lcd.print(3);
            j++;
            break;
          case 4 : pathArray[j] = 4;
            lcd.print(4);
            j++;
            break;
        }
      }
    }
  }
 if (beep) {
    digitalWrite(MOTOR_RIGHT_IN1, LOW);
    analogWrite(MOTOR_RIGHT_IN2, LOW);
    digitalWrite(MOTOR_LEFT_IN3, LOW);
    analogWrite(MOTOR_LEFT_IN4, LOW);
  } else {
    digitalWrite(MOTOR_RIGHT_IN1, HIGH);
    analogWrite(MOTOR_RIGHT_IN2, 10);
    digitalWrite(MOTOR_LEFT_IN3, HIGH);
    analogWrite(MOTOR_LEFT_IN4, 75);
  }

  if (!beep)
    morse(three);
  if (!beep)
    morse(one);
  if (!beep)
    morse(two);
  if (!beep)
    morse(five);
  if (!beep)
    morse(four);
  if (!beep) {
    for (int i = 0; i < 6; i++) {
      tone(buzzer, mario[i], 100);
      delay(100);
    }
    delay(500);
  }

  if (sonar.ping() / US_ROUNDTRIP_CM < 5)
    beep = false;
}

void check() {
  if (pathArray[4] != 0) {
    delay(300);
    for (int k = 0; k < 5; k++) {
      if (pathArray[k] != targetArray[k]) {
        lcd.clear();
        lcd.print("WRONG! TRY AGAIN!");
        for (k = 0; k < 5; k++) {
          pathArray[k] = 0;
        }
        j = 0;
        delay(1000);
        lcd.clear();
        lcd.print("INPUT PIN:");
        lcd.setCursor(0,1);
        return;
      }
    }
    lcd.clear();
    lcd.print("New code:");
    lcd.setCursor(0,1);
    lcd.print("ASPACEODYSSEY");
    delay(10000);
  }
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
