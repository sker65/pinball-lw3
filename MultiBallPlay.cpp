/*
 * MultiBallPlay.cpp
 *
 *  Created on: 04.09.2015
 *      Author: sr
 */

#include "MultiBallPlay.h"

MultiBallPlay::MultiBallPlay(const int* index, int num, int animationSpeed) : Effect(0,index,num) {
	this->animationDelay = 1000 / animationSpeed;
	paletteIndex = 0;
	nextUpdate = 0;
	SetupBlackAndWhiteStripedPalette();
}

void MultiBallPlay::SetupBlackAndWhiteStripedPalette() {
	// 'black out' all 16 palette entries...
	fill_solid(pal, 16, CRGB::Black);
	// and set every fourth one to white.
	pal[0] = CRGB::White;
	pal[4] = CRGB::White;
	pal[8] = CRGB::White;
	pal[12] = CRGB::White;

}

void MultiBallPlay::updateLeds(unsigned long now, CRGB* leds) {
	if (active && now > nextUpdate) {
		nextUpdate = now + animationDelay;
		paletteIndex = paletteIndex + 1; /* motion speed */
		int colorIndex = paletteIndex;

		for (int i = 0; i < num; i++) {
			leds[index[i]] = ColorFromPalette(pal, colorIndex, 255, NOBLEND);
			colorIndex += 3;
		}
	}

}
