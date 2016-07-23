const int controls[] = {2, 3, 4};
const int motors[] = {5, 6, 7, 8, 9, 10};

void setup() {
  for (int a = 0; a < 3; a++)
    pinMode(controls[a], INPUT);

  for (int a = 0; a < 6; a++)
    pinMode(motors[a], OUTPUT); 
  
}

void loop() {


}
