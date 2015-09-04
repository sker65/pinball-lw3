/*
 * SwitchScanner.h
 *
 *  Created on: 04.09.2015
 *      Author: sr
 */

#ifndef PINBALL_LW3_SWITCHSCANNER_H_
#define PINBALL_LW3_SWITCHSCANNER_H_

#include <Arduino.h>
#include "SwitchAction.h"

enum Trigger { EDGE, PERIODIC };

class ActionEntry {
public:
	SwitchAction* action;
	int col;
	byte rowMask;
	Trigger trigger;
};


#define LAST_COL_TO_READ 7
#define MAX_HANDLERS 20


class SwitchScanner {
public:
	SwitchScanner(uint32_t delay);
	virtual ~SwitchScanner();

	void readSwitches();
	void registerSwitchAction(int col, int row, SwitchAction* action);

	void update(uint32_t now);

	void printbin(byte bin);

	int handlerIndex;
	ActionEntry handlers[MAX_HANDLERS];

	boolean led;

	uint32_t nextPeriodic;
	uint32_t delay;

	volatile int col;
	// two times 8 byte for row returns
	// two arrays are used to detect changes
	volatile byte rows[2][8];
	// switches from 0 to 1 and back
	volatile int rowIndex;

	volatile int pin;

	volatile boolean switchChanged;

};


#endif /* PINBALL_LW3_SWITCHSCANNER_H_ */
