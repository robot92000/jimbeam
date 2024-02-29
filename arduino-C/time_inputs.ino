int redPin = 8;
int redOffTime = 250;
int redNumBlink = 1;
int redSecInput;

int bluePin = 9;
int blueOffTime = 250;
int blueNumBlink = 1;
int blueSecInput;

String redMessage = "The Red LED is ON for...";
String blueMessage = "The Blue LED is ON for...";
String space = " ";


void setup() {
	Serial.begin(9600);
	String wm1 = "Welcome to ";
	String wm2 = "my Time Program!";
	String wm3;
	wm3 = wm1 + wm2;
	Serial.println(wm3);
	Serial.println(space);
	pinMode(redPin, OUTPUT);
	pinMode(bluePin, OUTPUT);
	Serial.println("How long do you want Red to be on? (seconds)");
	while (Serial.available()==0) {}
	redSecInput = Serial.parseInt();
	Serial.print(redNumBlink);
	Serial.println(" seconds!");
	Serial.println("How long do you want Blue to be on? (seconcds)");
	while (Serial.available()==0) {}
	blueSecInput = Serial.parseInt();
	Serial.print(blueSecInput);
	Serial.println(" seconds!");
	Serial.println(space);
}


void loop() {
	Serial.println(redMessage);
	for (int i = 1; i <= redNumBlink; i=i+1) {
		Serial.print("   ");
		Serial.print(redSecInput);
		Serial.println(" seconds");
		digitalWrite(redPin, HIGH);
		delay(redSecInput * 1000);
		digitalWrite(redPin, LOW);
		delay(redOffTime);
	}
	Serial.println(space);
	Serial.println(blueMessage);
	for (int i = 1; i <= blueNumBlink; i=i+1) {
		Serial.print("   ");
		Serial.print(blueSecInput);
		Serial.println(" seconds");
		digitalWrite(bluePin, HIGH);
		delay(blueSecInput * 1000);
		digitalWrite(bluePin, LOW);
		delay(blueOffTime);
	}
	Serial.println(space);
}