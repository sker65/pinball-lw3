/*
 * NormalPlay.cpp
 *
 *  Created on: 04.09.2015
 *      Author: sr
 */

#include "NormalPlay.h"

// HSV Rainbow
extern const TProgmemRGBPalette16 redBluePallette PROGMEM = { 0x00FF00,
		0x800080, 0x0000FF, 0x800080, 0x00FF00, 0x800080, 0x0000FF, 0x800080,
		0x00FF00, 0x800080, 0x0000FF, 0x800080, 0x00FF00, 0x800080, 0x0000FF,
		0x800080, };

NormalPlay::NormalPlay(int* index, int num, int animationSpeed) :
		Effect(0, index, num) {
	paletteIndex = 0;
	nextUpdate = 0;
	this->animationDelay = 1000 / animationSpeed;
}

void NormalPlay::updateLeds(unsigned long now, CRGB* leds) {
	if (active && now > nextUpdate) {
		nextUpdate = now + animationDelay;
		paletteIndex = paletteIndex + 1; /* motion speed */
		int colorIndex = paletteIndex;
		CRGBPalette16 pal = redBluePallette;

		for (int i = 0; i < num; i++) {
			leds[index[i]] = ColorFromPalette(pal, colorIndex, 255, BLEND);
			colorIndex += 3;
		}
	}
}
