/*
 * BallStore.cpp
 *
 *  Created on: 28.08.2015
 *      Author: sr
 */

#include "BallStore.h"
#include <Arduino.h>

BallStore::BallStore(int maxBalls) {
	this->maxBalls = maxBalls;
	this->balls = maxBalls;
	this->switches = (int*)malloc( sizeof(int)*maxBalls);
}

BallStore::~BallStore() {
}

void BallStore::onSwitchUpdate(bool active, int num) {
	switches[num%maxBalls] = (active?1:0);
	balls = 0;
	for( int i = 0; i<maxBalls; i++) {
		balls += switches[i];
	}
	Serial.print("Balls: ");Serial.println(balls);
}

