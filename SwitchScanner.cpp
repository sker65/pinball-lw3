/*
 * SwitchScanner.cpp
 *
 *  Created on: 04.09.2015
 *      Author: sr
 */

#include "SwitchScanner.h"
#include <TimerOne.h>
#include <FastLED.h>

SwitchScanner::SwitchScanner(uint32_t delay) {
	pin = 0x80;
	switchChanged = false;
	col = 0;
	rowIndex=0;
	handlerIndex = 0;
	led = false;
	this->delay =delay;
	nextPeriodic = 0L;
}

void SwitchScanner::registerSwitchAction(int col, int row, SwitchAction* action) {
	handlers[handlerIndex].action = action;
	handlers[handlerIndex].col = col;
	handlers[handlerIndex].rowMask = (1 << row);
	if( handlerIndex < MAX_HANDLERS ) handlerIndex++;
}



// this will called as interrupt routine triggered by timer 1
void SwitchScanner::readSwitches() {
	// row index for row to compare
	int row = rowIndex==1?0:1;

	// generate rect wave just to control timing with logic analyser
	pin = ~pin;
	PORTC = pin;

	// read row return
	rows[rowIndex][col] = PINA; // for mega this will be PIN 22 - 29

	// compare this row with the row read last time
	if( rows[rowIndex][col] != rows[row][col] ) {
		switchChanged = true;
	}

	// we read col 0 to 6
	if (col++ == LAST_COL_TO_READ) {
		col = 0;
		Timer1.stop();
		// update from with (or at end) of interrupt
		FastLED.show();
	}
}


SwitchScanner::~SwitchScanner() {
}

void SwitchScanner::update(uint32_t now) {
	if( now > nextPeriodic ) {
		nextPeriodic = now + delay;
		for (int h = 0; h < handlerIndex; h++) {
			if (handlers[h].trigger == PERIODIC ) {
				bool active = (rows[rowIndex][col] & handlers[h].rowMask) == LOW;
				handlers[h].action->onSwitchUpdate(active);
			}
		}
	}

	if (switchChanged) {
		int nrow = rowIndex == 1 ? 0 : 1;

		switchChanged = false;
		// scan handlers
		for (int h = 0; h < handlerIndex; h++) {
			if (handlers[h].col == col && handlers[h].trigger == EDGE) {
				if ((rows[nrow][col] & handlers[h].rowMask)
						!= (rows[rowIndex][col] & handlers[h].rowMask)) {
					Serial.println("handler fired...");
					bool active = (rows[rowIndex][col] & handlers[h].rowMask) == LOW;
					handlers[h].action->onSwitchUpdate(active);
				}
			}
		}

		// flash led just to show switch change was recognized
		led = ~led;
		digitalWrite(13, led);

		// dump switches to serial
		Serial.println("  7 6 5 4 3 2 1 0");
		for (int col = 0; col < LAST_COL_TO_READ; col++) {
			Serial.print(col);
			printbin(rows[rowIndex][col]);
		}
		// toggle row index to compare with
		rowIndex = nrow;
	}

}

/**
 * used for printing switch matrix to serial
 */
void SwitchScanner::printbin(byte bin) {
	for (byte mask = 0x80; mask; mask >>= 1) {
		Serial.print(mask & bin ? " ." : " *");
	}
	Serial.println();
}

