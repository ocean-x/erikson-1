void setup() {
	pinMode(13, OUTPUT);
}

void loop() {
	digitalWrite(13, HIGH);
	delay(100);
	digitalWrite(13, LOW);
	delay(100);
}

// I know this is blink, but yes, Git cannot detect empty files and I have nothing better to type at this moment.
