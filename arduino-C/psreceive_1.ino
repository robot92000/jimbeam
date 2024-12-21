#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// String rawInput ="";

const byte numXPos = 116; // 96
const byte numXPosBig = 104; //84

const byte openYPos = 0;
const byte pendYpos = 16;
const byte onHoldYPos = 32;
const byte solvedYPos = 48;

const byte baseXpos = 0;

byte openTix = 3;
byte pendTix = 10;
byte onHoldTix = 2;
byte solvedTix = 25;

void setup() {
	Serial.begin(9600);

	if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
		Serial.println(F("SSD1306 allocation failed"));
		for(;;);
	}
	display.clearDisplay();
	display.display();
	delay(250);





	// display.setTextSize(1);
	// display.setTextColor(WHITE);
	// display.setCursor(0, 0);
	// display.setTextWrap(true);

	// display.print("output:");
	// display.display();

	// while (Serial.available()==0) {}
	// rawInput = Serial.readString();
	// display.println(rawInput);
	// display.display();
}

void loop() {

	display.setTextColor(WHITE);
	// OPEN TICKETS: #
	display.setTextSize(2);
	display.setCursor(baseXpos, openYPos);
	display.print("OPEN: ");
	display.setTextSize(2);
	if (openTix >= 10) {
		display.setCursor(numXPosBig, openYPos);
	} else {

		display.setCursor(numXPos, openYPos);
	}
	display.print(openTix);

	// PENDING TICKETS: #
	display.setTextSize(2);
	display.setCursor(baseXpos, pendYpos);
	display.print("PENDING: ");
	display.setTextSize(2);
	if (pendTix >= 10) {
		display.setCursor(numXPosBig, pendYpos);
	} else {

		display.setCursor(numXPos, pendYpos);
	}
	display.print(pendTix);

	// ON-HOLD TICKETS: #
	display.setTextSize(2);
	display.setCursor(baseXpos, onHoldYPos);
	display.print("ON-HOLD: ");
	display.setTextSize(2);
	if (onHoldTix >= 10) {
		display.setCursor(numXPosBig, onHoldYPos);
	} else {

		display.setCursor(numXPos, onHoldYPos);
	}
	display.print(onHoldTix);

	// SOLVED TICKETS: #
	display.setTextSize(2);
	display.setCursor(baseXpos, solvedYPos);
	display.print("SOLVED: ");
	display.setTextSize(2);
	if (solvedTix >= 10) {
		display.setCursor(numXPosBig, solvedYPos);
	} else {

		display.setCursor(numXPos, solvedYPos);
	}
	display.print(solvedTix);



	// Debug
	Serial.print(display.getCursorX());
	Serial.print(",");
	Serial.println(display.getCursorY());



	// rawInput = Serial.readStringUntil('#');

	// character size 1 max X pos 126, max Y pos 56
	// i discover that the Y axis will just keep going.... will reset at Y64
	// if (display.getCursorY() >= 64) {
	// 	display.clearDisplay();
	// 	display.setCursor(0, 0);
	// }
	// display.print(rawInput);



	display.display();
}