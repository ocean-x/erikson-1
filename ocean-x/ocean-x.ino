  

#include <LiquidCrystal_I2C.h>
#include <NAxisMotion.h>
#include <Servo.h>
#include <Wire.h>

#define BACKLIGHT_PIN     13
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address

const int controls[] = {2, 3, 4};
const int verticalmotors[] = {8, 9, 10, 11};
const int motors[] = {5, 6};

Servo escLeft;
Servo escRight;
Servo escVertical1;
Servo escVertical2;
Servo escVertical3;
Servo escVertical4;

int input[3], output[3] = {0};

void setup() {

  pinMode(BACKLIGHT_PIN, OUTPUT);
  digitalWrite(BACKLIGHT_PIN, HIGH);

  lcd.begin(16, 2);
  lcd.home ();
  lcd.print("OCEANX CONTROL");
  lcd.setCursor(0,1);
  lcd.print("HELLO");
  delay(4000);

  for (int a = 0; a < 4; a++)
    pinMode(verticalmotors[a], OUTPUT);

  for (int a = 0; a < 2; a++)
    pinMode(motors[a], OUTPUT);

  escLeft.attach(motors[0]);
  escRight.attach(motors[1]);
  escVertical1.attach(verticalmotors[0]);
  escVertical2.attach(verticalmotors[1]);
  escVertical3.attach(verticalmotors[2]);
  escVertical4.attach(verticalmotors[3]);
}

void loop() {

  for (int a = 0; a < 3; ++a) {
    input[a] = analogRead(controls[a]);
    output[a] = map(input[a], 0, 1023, 700, 2000);
  }

  escLeft.write(output[0]);
  escRight.write(output[1]);
  escVertical1.write(output[2]);
  escVertical2.write(output[2]);
  escVertical3.write(output[2]);
  escVertical4.write(output[2]);
}
