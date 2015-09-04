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
}

BallStore::~BallStore() {
}

void BallStore::onSwitchUpdate(bool active) {
	if( active ) {
		if( balls< maxBalls) balls++;
	} else {
		if( balls>0) balls--;
	}
	Serial.print("Balls: ");Serial.println(balls);
}

