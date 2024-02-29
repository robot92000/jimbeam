int redPin = 8;
int bluePin = 9;
int redOnTime = 250;
int redOffTime = 250;
int blueOnTime = 250;
int blueOffTime = 250;
int redNumBlink;
int blueNumBlink;
String redMessage = "The Red LED is Blinking!!!1!11";
String blueMessage = "The Blue LED is Blinking!!!1!11";
String space = " ";


void setup() {
	Serial.begin(9600);
	String wm1 = "Welcome to ";                                                                                                                                            
	String wm2 = "my Blink Program!";
	String wm3;
	wm3 = wm1 + wm2;
	Serial.println(wm3);
	Serial.println(space);
	pinMode(redPin, OUTPUT);
	pinMode(bluePin, OUTPUT);
	Serial.println("How many times do you want Red to Blink?");
	while (Serial.available()==0) {}
	redNumBlink = Serial.parseInt();
	Serial.print(redNumBlink);
	Serial.println(" times!");
	Serial.println("How many times do you want Blue to Blink?");
	while (Serial.available()==0) {}
	blueNumBlink = Serial.parseInt();
	Serial.print(blueNumBlink);
	Serial.println(" times!");
	Serial.println(space);
}


void loop() {
	Serial.println(redMessage);
	for (int i = 1; i <= redNumBlink; i=i+1) {
		Serial.print("   Red ");
		Serial.println(i);
		digitalWrite(redPin, HIGH);
		delay(redOnTime);
		digitalWrite(redPin, LOW);
		delay(redOffTime);
	}
	Serial.println(space);
	Serial.println(blueMessage);
	for (int i = 1; i <= blueNumBlink; i=i+1) {
		Serial.print("   Blue ");
		Serial.println(i);
		digitalWrite(bluePin, HIGH);
		delay(blueOnTime);
		digitalWrite(bluePin, LOW);
		delay(blueOffTime);
	}
	Serial.println(space);
}