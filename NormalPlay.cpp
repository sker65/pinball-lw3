/*
 * NormalPlay.cpp
 *
 *  Created on: 04.09.2015
 *      Author: sr
 */

#include "NormalPlay.h"
#include "LedDriver.h"

// HSV Rainbow
extern const TProgmemRGBPalette16 redBluePallette PROGMEM = { 0x00FF00,
		0x0000FF, 0x0000FF, 0x0000FF, 0x00FF00, 0x00FF00, 0x00FF00, 0x0000FF,
		0x0000FF, 0x0000FF, 0x0000FF, 0x00FF00, 0x00FF00, 0x00FF00, 0x0000FF,
		0x00FF00, };

NormalPlay::NormalPlay(int* index, int num, int animationSpeed, int holdCycles) :
		Effect(0, index, num) {
	paletteIndex = 0;
	nextUpdate = 0;
	this->animationDelay = 1000 / animationSpeed;
	this->holdCycles = holdCycles;
	this->cycle = 0;
}

void NormalPlay::updateLeds(unsigned long now, CRGB* leds) {
	if (active && now > nextUpdate) {
		nextUpdate = now + animationDelay;

		// add a hold at 0, 16, 32
		if(( paletteIndex % 16)== 0 ) {
			if( cycle++ > holdCycles) {
				paletteIndex = paletteIndex + 1;
				cycle = 0;
			}
		} else {
			paletteIndex = paletteIndex + 1; /* color motion speed */
		}
		int colorIndex = paletteIndex;
		CRGBPalette16 pal = redBluePallette;

		for (int i = 0; i < num; i++) {
			leds[index[i]] = ColorFromPalette(pal, colorIndex, 255, LINEARBLEND);
		}

		for (int i = 0; i < 4; i++) {
			rightBat[i] = ColorFromPalette(pal, colorIndex, 180, LINEARBLEND);
			leftBat[i] = ColorFromPalette(pal, colorIndex, 180, LINEARBLEND);
		}

	}
}
