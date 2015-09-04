/*
 * SlingFlash.cpp
 *
 *  Created on: 31.08.2015
 *      Author: sr
 */

#include "SlingFlash.h"

SlingFlash::SlingFlash(Effect* effect) {
	this->effect = effect;
}

SlingFlash::~SlingFlash() {
}

void SlingFlash::onSwitchUpdate(bool active, int num){
	if( active ) effect->start();
}

