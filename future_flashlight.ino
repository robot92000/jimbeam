/*
MODES
	White
	RGB
	Police
	Party Strobe
*/
const int inputSetup[] = {A0, A1, A2, A3, 2, 3, 4, 5};

const int modeWhitePin = 2;
const int modeRGBPin = 3;
const int modePolicePin = 4;
const int modePartyPin = 5;

const int brightnessPotPin = A0;
const int redPotPin = A1;
const int greenPotPin = A2;
const int bluePotPin = A3;



const int ledPins[] = {9, 10, 11};
const int redPin = 9;
const int greenPin = 10;
const int bluePin = 11;



const int strobeDelay = 100;
const int partySequence[][3] = {{1, 0, 0},	// red
								{0, 1, 0},	// green
								{0, 0, 1},	// blue
								{1, 0, 1},	// cyan
								{1, 1, 0},	// yellow
								{1, 0, 1}};	// magenta

void setup() {
	for (int i = 0; i < sizeof(inputSetup); ++i) {
		pinMode(inputSetup[i], INPUT);
	}
	for (int i = 0; i < sizeof(ledPins); ++i) {
		pinMode(ledPins[i], OUTPUT);
	}
}

void blank() {
	for (int i = 0; i < sizeof(ledPins); ++i) {
		digitalWrite(ledPins[i], LOW);
	}
}

void checkWhiteMode() {
	if (digitalRead(modeWhitePin) == HIGH) {
		int whiteLevel = map(analogRead(brightnessPotPin), 0, 1020, 0, 255);
		for (int i = 0; i < sizeof(ledPins); ++i) {
			analogWrite(ledPins[i], whiteLevel);
		}
	} else {
		blank();
	}
}

void checkRGBMode() {
	if (digitalRead(modeRGBPin) == HIGH) {
		int redLevel = map(analogRead(redPotPin), 0, 1020, 0, 255);
		int greenLevel = map(analogRead(greenPotPin), 0, 1020, 0, 255);
		int blueLevel = map(analogRead(bluePotPin), 0, 1020, 0, 255);
		analogWrite(redPin, redLevel);
		analogWrite(greenPin, greenLevel);
		analogWrite(bluePin, blueLevel);
	} else {
		blank();
	}
}
void checkPoliceMode() {
	if (digitalRead(modePolicePin) == HIGH) {
		for (int i = 0; i <= 3; ++i) {
			digitalWrite(redPin, HIGH);
			delay(strobeDelay);
			digitalWrite(redPin, LOW);
			delay(strobeDelay);
		}
		for (int i = 0; i <= 3; ++i) {
			digitalWrite(bluePin, HIGH);
			delay(strobeDelay);
			digitalWrite(bluePin, LOW);
			delay(strobeDelay);
		}
	} else {
		blank();
	}
}

void checkPartyMode() {
	if (digitalRead(modePartyPin) == HIGH) {
		for (int i = 0; i < 5; ++i) {
			digitalWrite(redPin, partySequence[i][0]);
			digitalWrite(greenPin, partySequence[i][1]);
			digitalWrite(bluePin, partySequence[i][2]);
			delay(strobeDelay);
		}
	} else {
		blank();
	}
}

void loop() {
	checkWhiteMode();
	checkRGBMode();
	checkPoliceMode();
	checkPartyMode();
}