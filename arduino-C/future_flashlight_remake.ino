/*
welcome
*/
const int outputSetup[] = {9, 10, 11};
const int leds[] = {9, 10, 11};
const int redPin = 9;
const int greenPin = 10;
const int bluePin = 11;

const int inputSetup[] = {A0, A1, A2, A3, 5, 6, 7, 8};
const int redPotPin = A0;
const int greenPotPin = A1;
const int bluePotPin = A2;
const int brightnessPotPin = A3;

const int modePinRGB = 5;
const int modePinWhite = 6;
const int modePinPolice = 7;
const int modePinParty = 8;

int redLevel;
int greenLevel;
int blueLevel;
int brightnessLevel;

const int policeDelay = 50;
const int partyDelay = 100;

const int partyModeSequence[6][3] = {
									{1, 0, 0}, // red
									{0, 1, 0}, // green
									{0, 0, 1}, // blue
									{1, 1, 0}, // yellow
									{0, 1, 1}, // cyan
									{1, 0, 1}  // magenta
};

void setup() {
	for(int i = 0; i < sizeof(outputSetup); ++i) {
		pinMode(outputSetup[i], OUTPUT);
	}
	for(int i = 0; i < sizeof(inputSetup); ++i) {
		pinMode(inputSetup[i], INPUT);
	}
}

void blank() {
	for(int i = 0; i < sizeof(leds); ++i) {
		digitalWrite(leds[i], LOW);
	}
}

void modeRGB() {
	while(digitalRead(modePinRGB) == HIGH) {
		redLevel = map(analogRead(redPotPin), 0, 1020, 0, 255);
		greenLevel = map(analogRead(greenPotPin), 0, 1020, 0, 255);
		blueLevel = map(analogRead(bluePotPin), 0, 1020, 0, 255);
		analogWrite(redPin, redLevel);
		analogWrite(greenPin, greenLevel);
		analogWrite(bluePin, blueLevel);
	}
	blank();
}

void modeWhite() {
	while(digitalRead(modePinWhite) == HIGH) {
		brightnessLevel = map(analogRead(brightnessPotPin), 0, 1020, 0, 255);
		for(int i = 0; i < sizeof(leds); ++i) {
			analogWrite(leds[i], brightnessLevel);
		}		
	}
	blank();
}

void modePolice() {
	while(digitalRead(modePinPolice) == HIGH) {
		for(int i = 0; i <= 3; ++i) {
			digitalWrite(redPin, HIGH);
			delay(policeDelay);
			digitalWrite(redPin, LOW);
			delay(policeDelay);
		}
		for(int i = 0; i <= 3; ++i) {
			digitalWrite(bluePin, HIGH);
			delay(policeDelay);
			digitalWrite(bluePin, LOW);
			delay(policeDelay);
		}
	}
	blank();
}

void modeParty() {
	while(digitalRead(modePinParty) == HIGH) {
		for(int i = 0; i < 6; ++i) {
			digitalWrite(leds[0], partyModeSequence[i][0]);
			digitalWrite(leds[1], partyModeSequence[i][1]);
			digitalWrite(leds[2], partyModeSequence[i][2]);
			delay(partyDelay);
		}
	}
	blank();
}

void loop() {
	modeRGB();
	modeWhite();
	modePolice();
	modeParty();
}