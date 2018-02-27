#include <MIDI.h>
#include <midi_Defs.h>
#include <midi_Message.h>
#include <midi_Namespace.h>
#include <midi_Settings.h>


// Pin Definitions
// Rows are connected to
const int row1 = 5;
const int row2 = 6;
const int row3 = 7;
const int row4 = 8;
 
//Pin connected to SH_CP of 74HC595
const int clock = 8;
//Pin connected to ST_CP of 74HC595
const int latch = 9;
//Pin connected to ST_CP of 74HC595
const int data = 10;
 
 
byte keyToMidiMap[32];
 
boolean keyPressed[32];
 
int noteVelocity = 127;
 
 
// use prepared bit vectors instead of shifting bit left everytime
int bits[] = { B00000001, B00000010, B00000100, B00001000, B00010000, B00100000, B01000000, B10000000 };
 
MIDI_CREATE_DEFAULT_INSTANCE(); 
// 74HC595 shift to next column
void scanColumn(int value) {
	digitalWrite(latch, LOW); //Pulls the chips latch low
	shiftOut(data, clock, MSBFIRST, value); //Shifts out the 8 bits to the shift register
	digitalWrite(latch, HIGH); //Pulls the latch high displaying the data
}
 
void setup() {
	
	// Map scan matrix buttons/keys to actual Midi note number. Lowest num 41 corresponds to F MIDI note.
	keyToMidiMap[0] = 84;
	keyToMidiMap[1] = 83;
	keyToMidiMap[2] = 82;
	keyToMidiMap[3] = 81;
	keyToMidiMap[4] = 81;
	keyToMidiMap[5] = 79;
	keyToMidiMap[6] = 78;
	keyToMidiMap[7] = 76;
 
	keyToMidiMap[8] = 75;
	keyToMidiMap[1 + 8] = 74;
	keyToMidiMap[2 + 8] = 62;
	keyToMidiMap[3 + 8] = 61;
	keyToMidiMap[4 + 8] = 60;
	keyToMidiMap[5 + 8] = 59;
	keyToMidiMap[6 + 8] = 58;
	keyToMidiMap[7 + 8] = 57;
 
	keyToMidiMap[16] = 56;
	keyToMidiMap[1 + 16] = 55;
	keyToMidiMap[2 + 16] = 54;
	keyToMidiMap[3 + 16] = 53;
	keyToMidiMap[4 + 16] = 52;
	keyToMidiMap[5 + 16] = 51;
	keyToMidiMap[6 + 16] = 50;
	keyToMidiMap[7 + 16] = 49;
 
	keyToMidiMap[24] = 48;
	keyToMidiMap[1 + 24] = 47;
	keyToMidiMap[2 + 24] = 46;
	keyToMidiMap[3 + 24] = 45;
	keyToMidiMap[4 + 24] = 44;
	keyToMidiMap[5 + 24] = 43;
	keyToMidiMap[6 + 24] = 42;
	keyToMidiMap[7 + 24] = 41;
 
	// setup pins output/input mode
	pinMode(data, OUTPUT);
	pinMode(clock, OUTPUT);
	pinMode(latch, OUTPUT);
 
	pinMode(row1, INPUT);
	pinMode(row2, INPUT);
	pinMode(row3, INPUT);
	pinMode(row4, INPUT);
        MIDI.begin(1);
	delay(100);
 
}
 
void loop() {
 
	for (int col = 0; col < 8; col++) {
		
		// shift scan matrix to following column
		scanColumn(bits[col]);
 
		// check if any keys were pressed - rows will have HIGH output in this case corresponding
		int groupValue1 = digitalRead(row1);
		int groupValue2 = digitalRead(row2);
		int groupValue3 = digitalRead(row3);
		int groupValue4 = digitalRead(row4);
 
		// process if any combination of keys pressed
		if (groupValue1 != 0 || groupValue2 != 0 || groupValue3 != 0
				|| groupValue4 != 0) {
 
			if (groupValue1 != 0 && !keyPressed[col]) {
				keyPressed[col] = true;
                                MIDI.sendNoteOn(keyToMidiMap[col], noteVelocity, 1);
			}
 
			if (groupValue2 != 0 && !keyPressed[col + 8]) {
				keyPressed[col + 8] = true;
				MIDI.sendNoteOn(keyToMidiMap[col + 8], noteVelocity, 1);;
			}
 
			if (groupValue3 != 0 && !keyPressed[col + 16]) {
				keyPressed[col + 16] = true;
				MIDI.sendNoteOn(keyToMidiMap[col + 16], noteVelocity, 1);
			}
 
			if (groupValue4 != 0 && !keyPressed[col + 24]) {
				keyPressed[col + 24] = true;
				MIDI.sendNoteOn(keyToMidiMap[col + 24], noteVelocity, 1);
			}
 
		}
 
		//  process if any combination of keys released
		if (groupValue1 == 0 && keyPressed[col]) {
			keyPressed[col] = false;
			MIDI.sendNoteOff(keyToMidiMap[col], noteVelocity, 1);
		}
 
		if (groupValue2 == 0 && keyPressed[col + 8]) {
			keyPressed[col + 8] = false;
			MIDI.sendNoteOff(keyToMidiMap[col + 8], noteVelocity, 1);
		}
 
		if (groupValue3 == 0 && keyPressed[col + 16]) {
			keyPressed[col + 16] = false;
			MIDI.sendNoteOff(keyToMidiMap[col + 16], noteVelocity, 1);
		}
 
		if (groupValue4 == 0 && keyPressed[col + 24]) {
			keyPressed[col + 24] = false;
			MIDI.sendNoteOff(keyToMidiMap[col + 24], noteVelocity, 1);
		}
 
	}
 
}
 
 

