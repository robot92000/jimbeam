#include <FastLED.h>

#define NUM_LEDS 16
#define LED_DATA_PIN 2

CRGB shifterLeds[NUM_LEDS];

//	Inputs
const int selSolidColor = 3;
const int selChill = 4;
const int selBoolMode = 5;
const int illuminationSig = 6;
const int ignitionSignalInput = 7;
const int huePot = A0;
const int testRPM = A1;

//	Variables
int masterBrightness;
int hueValue;
// const int chillRangeStart = 128;
// const int chillRangeStop = 224;
// int chillHueValue = chillRangeStart;

// Chill Mode Gradient
DEFINE_GRADIENT_PALETTE (chill_grad1) {
	  0,   0, 255, 255, // Cyan
	 64,   0,   0, 255, // Blue
	 96, 127,   0, 255, // Purple
	192, 255,   0, 255, // Magenta
	255,   0, 255, 255  // Cyan
};
CRGBPalette16 chillPallet1 = chill_grad1;
uint8_t paletteIndex = 0;

//  RPM Reader Variables
// long highPulse;
// long lowPulse;
// long cycleTime;
// float cycleFreq;
// int cylinderFreq;
int EJ20RPM;

//  Bool Mode Variables
int ejBoolIdleRPM = 450;   // Pink
int ejBoolStartRPM = 3500; // Yellow
int ejBoolMidRPM = 4500;   // Red
int ejBoolHighRPM = 5500;  // Red Flashing \/
int ejBoolMaxRPM = 6500;

// LED Select Idle to Start Range
int boolLEDIdleToStartRangeLeft;
int boolLEDIdleToStartRangeRight;

// LED Select Start to Mid Range
int boolLEDStartToMidRangeLeft;
int boolLEDStartToMidRangeRight;

// LED Select Mid to High Range
int boolLEDMidToHighRangeLeft;
int boolLEDMidToHighRangeRight;

// LED Range Map Operators
int varNumLED = 16;
int leftLEDRangeMax = (varNumLED / 2) - 1;
int rightLEDRangeMax = varNumLED;
int rightLEDRangeMin = varNumLED / 2;


void setup() {
	FastLED.addLeds<WS2812B, LED_DATA_PIN, GRB>(shifterLeds, NUM_LEDS);
	pinMode(selSolidColor, INPUT);
	pinMode(selChill, INPUT);
	pinMode(selBoolMode, INPUT);
	pinMode(illuminationSig, INPUT);
	pinMode(huePot, INPUT);
	pinMode(testRPM, INPUT);
	pinMode(ignitionSignalInput, INPUT);
	Serial.begin(9600);
}

void loop() {
	// Serial.print("Tail Light Circuit: ");
	solidColor();
	chillMode();
	boolMode();
}

void brightnessControl() {
	Serial.print("Parking Light = ");
	if (digitalRead(illuminationSig) == HIGH) {
		masterBrightness = 64;
		Serial.print("On ");
	} else {
		masterBrightness = 255;
		Serial.print("Off ");
	}
	FastLED.setBrightness(masterBrightness);
}

void boolMode() {
	while (digitalRead(selBoolMode) == HIGH) {
		brightnessControl();
		EJ20RPM = map(analogRead(testRPM), 0, 1024, 0, 6500);

		serialDebug("Bool Mode", EJ20RPM);
		// highPulse = pulseIn(ignitionSignalInput, 1000);
		// lowPulse = pulseIn(ignitionSignalInput, LOW);
		// cycleTime = highPulse + lowPulse;
		// cycleFreq = 1000000 / cycleTime;
		// cylinderFreq = cycleFreq * 60;
		// EJ20RPM = cylinderFreq * 4;

		if (EJ20RPM == 0) {
			for (int i = 0; i < NUM_LEDS; ++i) {
				shifterLeds[i] = CHSV(0, 255, 0);
			}
			FastLED.show();
		} else {
			// Idle to Start RPM Range
			if (EJ20RPM >= ejBoolIdleRPM && EJ20RPM < ejBoolStartRPM) {

				boolLEDIdleToStartRangeLeft = map(EJ20RPM, ejBoolIdleRPM, ejBoolStartRPM, leftLEDRangeMax, -1);
				boolLEDIdleToStartRangeRight = map(EJ20RPM, ejBoolIdleRPM, ejBoolStartRPM, rightLEDRangeMin, rightLEDRangeMax);

				Serial.print("Left:");
				Serial.print(boolLEDIdleToStartRangeLeft);
				Serial.print(" Right:");
				Serial.print(boolLEDIdleToStartRangeRight);
				Serial.print(" | ");

				for (int i = 7; i >= boolLEDIdleToStartRangeLeft; --i) {
					shifterLeds[i] = CHSV(220, 255, 255);
				}
				for (int i = boolLEDIdleToStartRangeRight; i > leftLEDRangeMax ; --i) {
					shifterLeds[i] = CHSV(220, 255, 255);
				}

				//Now we turn off the Upper LEDs since we aint ther yet
				for (int i = 0; i <= boolLEDIdleToStartRangeLeft - 1; ++i) {
					shifterLeds[i] = CHSV(0, 255, 0);
				}
				for (int i = rightLEDRangeMax; i > boolLEDIdleToStartRangeRight ; --i) {
					shifterLeds[i] = CHSV(0, 255, 0);
				}
			}
			// Start to Mid RPM Range
			if (EJ20RPM >= ejBoolStartRPM && EJ20RPM < ejBoolMidRPM) {

				boolLEDStartToMidRangeLeft = map(EJ20RPM, ejBoolStartRPM, ejBoolMidRPM, leftLEDRangeMax, -1);
				boolLEDStartToMidRangeRight = map(EJ20RPM, ejBoolStartRPM, ejBoolMidRPM, rightLEDRangeMin, rightLEDRangeMax);

				for (int i = 7; i >= boolLEDStartToMidRangeLeft; --i) {
					shifterLeds[i] = CHSV(60, 255, 255);
				}
				for (int i = boolLEDStartToMidRangeRight; i > leftLEDRangeMax ; --i) {
					shifterLeds[i] = CHSV(60, 255, 255);
				}
				
				//Now we turn off the Upper LEDs since we aint ther yet
				for (int i = 0; i <= boolLEDStartToMidRangeLeft - 1; ++i) {
					shifterLeds[i] = CHSV(220, 255, 255);
				}
				for (int i = rightLEDRangeMax; i > boolLEDStartToMidRangeRight ; --i) {
					shifterLeds[i] = CHSV(220, 255, 255);
				}
			}
			// Mid to High RPM Range
			if (EJ20RPM >= ejBoolMidRPM && EJ20RPM < ejBoolHighRPM) {

				boolLEDMidToHighRangeLeft = map(EJ20RPM, ejBoolMidRPM, ejBoolHighRPM, leftLEDRangeMax, -1);
				boolLEDMidToHighRangeRight = map(EJ20RPM, ejBoolMidRPM, ejBoolHighRPM, rightLEDRangeMin, rightLEDRangeMax);

				for (int i = 7; i >= boolLEDMidToHighRangeLeft; --i) {
					shifterLeds[i] = CHSV(0, 255, 255);
				}
				for (int i = boolLEDMidToHighRangeRight; i > leftLEDRangeMax ; --i) {
					shifterLeds[i] = CHSV(0, 255, 255);
				}
				
				//Now we turn off the Upper LEDs since we aint ther yet
				for (int i = 0; i <= boolLEDMidToHighRangeLeft - 1; ++i) {
					shifterLeds[i] = CHSV(60, 255, 255);
				}
				for (int i = rightLEDRangeMax; i > boolLEDMidToHighRangeRight ; --i) {
					shifterLeds[i] = CHSV(60, 255, 255);
				}
			}
			// High to Max RPM Range
			if (EJ20RPM >= ejBoolHighRPM && EJ20RPM < ejBoolMaxRPM) {
				for (int i = 0; i < NUM_LEDS; ++i) {
					shifterLeds[i] = CHSV(0, 255, 255);
				}
				EVERY_N_MILLISECONDS(200) {
					FastLED.show();
				}
				for (int i = 0; i < NUM_LEDS; ++i) {
					shifterLeds[i] = CHSV(0, 255, 0);
				}
				EVERY_N_MILLISECONDS(500) {
					FastLED.show();
				}
			}
			FastLED.show();
		}
	}
}

void solidColor() {
	while (digitalRead(selSolidColor) == HIGH) {
		brightnessControl();
		serialDebug("Solid Color", hueValue);
		hueValue = map(analogRead(huePot), 0, 1020, 0, 255);
		for (int i = 0; i < NUM_LEDS; i++) {
			shifterLeds[i] = CHSV(hueValue, 255, 255);
		}
	FastLED.show();
	}
}

void chillMode() {
	while (digitalRead(selChill) == HIGH) {
		brightnessControl();
		serialDebug("Chill Mode", paletteIndex);
		fill_palette(shifterLeds, NUM_LEDS, paletteIndex, 255 / NUM_LEDS, chillPallet1, 255, LINEARBLEND);
		EVERY_N_MILLISECONDS(20) {
			paletteIndex = paletteIndex + 3;
		}
		FastLED.show();
	}
}

void serialDebug(char currentMode[], int debugValue) {
	Serial.print("Tail Light Circuit: ");
	//Serial.print(digitalRead(illuminationSig));
	Serial.print(" Selected mode: ");
	Serial.print(currentMode);
	if (currentMode == "Bool Mode") {
		Serial.print(" RPM: ");
		Serial.println(debugValue);
	} 
	if (currentMode == "Solid Color") {
		Serial.print(" Hue Value: ");
		Serial.println(debugValue);
	}
	if (currentMode == "Chill Mode") {
		Serial.print(" Palette Index: ");
		Serial.println(debugValue);
	}

}
