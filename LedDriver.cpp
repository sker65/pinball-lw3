/*
 * LedDriver.cpp
 *
 *  Created on: 31.08.2015
 *      Author: sr
 */

#include "LedDriver.h"

#define LED_PIN     12
#define NUM_LEDS    36
#define BRIGHTNESS  255
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

LedDriver::LedDriver(int updatesPerSecond) {
	this->nextUpdate = 0;
	this->millisBetweenUpdates = 1000 / updatesPerSecond;
	FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(
			TypicalPixelString);
	FastLED.setBrightness( BRIGHTNESS );
	numberOfEffects = 0;
}

LedDriver::~LedDriver() {
}

void LedDriver::update(uint32_t now) {
	// render effects
	int level = 0;
	while(level < 2) {
		for( int i = 0; i < numberOfEffects; i++) {
			if( effects[i]->level == level ) {
				effects[i]->updateLeds(now, leds);
			}
		}
		level++;
	}
//	if (now > nextUpdate) {
//		nextUpdate = now + millisBetweenUpdates;
//		FastLED.show();
//	}
}

void LedDriver::registerEffect(Effect* effect) {
	effects[numberOfEffects++] = effect;
}
