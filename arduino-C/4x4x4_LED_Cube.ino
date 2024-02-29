const int dataPin = 13;
const int clockPin = 12;
const int latchPin = 11;
const int masterClearPin = 10;

const int anodeLevel[] = {8, 7, 6, 5};

const byte cathodeColumn[4][4][2] = {  // [x][z][register]
	{{0x10,0x00},{0x20,0x00},{0x40,0x00},{0x80,0x00}},

	{{0x01,0x00},{0x02,0x00},{0x04,0x00},{0x08,0x00}},

	{{0x00,0x10},{0x00,0x20},{0x00,0x40},{0x00,0x80}},

	{{0x00,0x01},{0x00,0x02},{0x00,0x04},{0x00,0x08}}
};


byte combineLevelCathodeData(byte byteCombine[][2], int bytePosition) { // use OR operator to combine led outputs on a level to one byte at a time
	byte combinedByte;
	for (int i = 0; i < sizeof(byteCombine); ++i) {
		combinedByte |= byteCombine[i][bytePosition];
	}
	return combinedByte;
}

byte testStatic[][2] = { // all 4 corners
	{cathodeColumn[0][0][0], cathodeColumn[0][0][1]},
	{cathodeColumn[0][3][0], cathodeColumn[0][3][1]},
	{cathodeColumn[3][0][0], cathodeColumn[3][0][1]},
	{cathodeColumn[3][3][0], cathodeColumn[3][3][1]},
};

void setup() {
	for (int i = 0; i < sizeof(anodeLevel); ++i) {
		pinMode(i, OUTPUT);
	}
	pinMode(dataPin, OUTPUT);
	pinMode(clockPin, OUTPUT);
	pinMode(latchPin, OUTPUT);
	pinMode(masterClearPin, OUTPUT);
	digitalWrite(masterClearPin, HIGH);
}

void loop() {
	singleLedDisplay(1, 1, 1);
	runTestStatic();
}

void runTestStatic() {
	for (int i = 0; i < sizeof(anodeLevel); ++i) {
		if (i >= 1) {
			digitalWrite(anodeLevel[i-1], LOW);
		}
		digitalWrite(anodeLevel[i], HIGH);
		if (i == 0) {
			dataShift(combineLevelCathodeData(testStatic, 0), combineLevelCathodeData(testStatic, 1));
		} else {
			blankLevel();
		}
		if (i == 1) {
		} else {
			blankLevel();
		}
		if (i == 2) {
		} else {
			blankLevel();
		}
		if (i == 3) {
			dataShift(combineLevelCathodeData(testStatic, 0), combineLevelCathodeData(testStatic, 1));
		} else {
			blankLevel();
		}
	}
}

void singleLedDisplay(int x, int y, int z) { // for displaying one LED at a time
	x -= 1;
	y -= 1;
	z -= 1;
	for (int i = 0; i < sizeof(anodeLevel); ++i) {
		if (i >= 1) {
			digitalWrite(anodeLevel[i-1], LOW);
		}
		digitalWrite(anodeLevel[i], HIGH);
		if (y == i) {
			dataShift(cathodeColumn[x][z][0], cathodeColumn[x][z][1]);
		}
	}
}

void blankLevel() {
	dataShift(0x00, 0x00);
}
void cubeTest() { // test if all LEDs are working
	for (int i = 0; i < sizeof(anodeLevel); ++i) {
		digitalWrite(anodeLevel[i], HIGH);
	}
	dataShift(0xff, 0xff);
}
void dataShift(byte registerOne, byte registerTwo) { // send 2nd place (1) of 3rd dimention first
	digitalWrite(latchPin, LOW);
	shiftOut(dataPin, clockPin, LSBFIRST, registerTwo);
	shiftOut(dataPin, clockPin, LSBFIRST, registerOne);
	digitalWrite(latchPin, HIGH);
}
