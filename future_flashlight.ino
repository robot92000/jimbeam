/*
MODES
	White
	RGB
	Police
	Party Strobe

	Code for atmega328p using arduino IDE for 100W RGB LED Flashlight

	to further understand the Arduino IDE, go here: https://www.arduino.cc/reference/en/
*/

// defining intputs
const int inputSetup[] = {A0, A1, A2, A3, 2, 3, 4, 5}; // easier to define pinmodes in array
//actual used names for pins
const int modeWhitePin = 2; // rotary switch will pull one pin high at a time
const int modeRGBPin = 3;
const int modePolicePin = 4;
const int modePartyPin = 5;

const int brightnessPotPin = A0; // analog inputs for brightness levels using potentiometers
const int redPotPin = A1;
const int greenPotPin = A2;
const int bluePotPin = A3;

//defining outputs (only specific pins can be used for pwm output, will still work with digital 1 or 0)
const int ledPins[] = {9, 10, 11}; // define pinmodes in array
const int redPin = 9;
const int greenPin = 10;
const int bluePin = 11;



const int strobeDelay = 100; // in miliseconds
const int partySequence[][3] = {{1, 0, 0},	// red
								{0, 1, 0},	// green
								{0, 0, 1},	// blue
								{1, 0, 1},	// cyan
								{1, 1, 0},	// yellow
								{1, 0, 1}};	// magenta

void setup() {	//first executed code, pretty much "main()"
	for (int i = 0; i < sizeof(inputSetup); ++i) {
		pinMode(inputSetup[i], INPUT);
	}
	for (int i = 0; i < sizeof(ledPins); ++i) {
		pinMode(ledPins[i], OUTPUT);
	}
} // after this, will start running loop() located at the bottom of the script

void blank() { // turn all lights off
	for (int i = 0; i < sizeof(ledPins); ++i) {
		digitalWrite(ledPins[i], LOW);
	}
}

void checkWhiteMode() { // mode for solid white light with brightness controll
	if (digitalRead(modeWhitePin) == HIGH) { // check for mode pin as HIGH
		int whiteLevel = map(analogRead(brightnessPotPin), 0, 1020, 0, 255);
		for (int i = 0; i < sizeof(ledPins); ++i) {
			analogWrite(ledPins[i], whiteLevel);
		}
	} else { // turn off if mode not selected
		blank();
	}
}

void checkRGBMode() { // mode for RGB color selection with potentiometers
	if (digitalRead(modeRGBPin) == HIGH) {
		int redLevel = map(analogRead(redPotPin), 0, 1020, 0, 255); // maps to convert 10bit value to 8 bit for analogWrite() (pwm)
		int greenLevel = map(analogRead(greenPotPin), 0, 1020, 0, 255);
		int blueLevel = map(analogRead(bluePotPin), 0, 1020, 0, 255);
		analogWrite(redPin, redLevel);
		analogWrite(greenPin, greenLevel);
		analogWrite(bluePin, blueLevel);
	} else {
		blank();
	}
}

void checkPoliceMode() { // mode for police light animation
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

void checkPartyMode() { // mode for party strobe with pre programed colors in 2d array
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

void loop() { // loop will run through functions as they check themselves for on-state
	checkWhiteMode();
	checkRGBMode();
	checkPoliceMode();
	checkPartyMode();
}
