/*
 * Attract.cpp
 *
 *  Created on: 31.08.2015
 *      Author: sr
 */

#include "Attract.h"
#include "LedDriver.h"

//extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;

Attract::Attract(const int* index, int num, int animationSpeed) : Effect(0, index, num) {
	currentPalette = RainbowColors_p;
	currentBlending = BLEND;
	startIndex = 0;
	nextUpdate = 0;
	this->animationDelay = 1000 / animationSpeed;
}

void Attract::updateLeds(unsigned long now, CRGB* leds) {
	if( active && now > nextUpdate) {
		nextUpdate = now + animationDelay;
		ChangePalettePeriodically();
		startIndex = startIndex + 1; /* motion speed */
		uint8_t brightness = 255;
		int colorIndex = startIndex;

		for (int i = 0; i < num; i++) {
			leds[index[i]] = ColorFromPalette(currentPalette, colorIndex, brightness,
					currentBlending);
			colorIndex += 3;
		}

//		for (int i = 0; i < 4; i++) {
//			rightBat[i] = ColorFromPalette(currentPalette, colorIndex, 180, BLEND);
//			leftBat[i] = ColorFromPalette(currentPalette, colorIndex, 180, BLEND);
//		}

	}
}

// There are several different palettes of colors demonstrated here.
//
// FastLED provides several 'preset' palettes: RainbowColors_p, RainbowStripeColors_p,
// OceanColors_p, CloudColors_p, LavaColors_p, ForestColors_p, and PartyColors_p.
//
// Additionally, you can manually define your own color palettes, or you can write
// code that creates color palettes on the fly.  All are shown here.

void Attract::ChangePalettePeriodically() {
	uint8_t secondHand = (millis() / 1000) % 130;
	static uint8_t lastSecond = 255;

	if (lastSecond != secondHand) {
		lastSecond = secondHand;
		if (secondHand == 0) {
			currentPalette = RainbowColors_p;
			currentBlending = BLEND;
		}
		if (secondHand == 20) {
			currentPalette = RainbowStripeColors_p;
			currentBlending = NOBLEND;
		}
		if (secondHand == 40) {
			currentPalette = RainbowStripeColors_p;
			currentBlending = BLEND;
		}
		if (secondHand == 50) {
			SetupPurpleAndGreenPalette();
			currentBlending = BLEND;
		}
		if (secondHand == 60) {
			SetupTotallyRandomPalette();
			currentBlending = BLEND;
		}
		if (secondHand == 65) {
			SetupBlackAndWhiteStripedPalette();
			currentBlending = NOBLEND;
		}
		if (secondHand == 75) {
			SetupBlackAndWhiteStripedPalette();
			currentBlending = BLEND;
		}
		if (secondHand == 85) {
			currentPalette = CloudColors_p;
			currentBlending = BLEND;
		}
		if (secondHand == 95) {
			currentPalette = PartyColors_p;
			currentBlending = BLEND;
		}
		if (secondHand == 110) {
			currentPalette = myRedWhiteBluePalette_p;
			currentBlending = NOBLEND;
		}
		if (secondHand == 120) {
			currentPalette = myRedWhiteBluePalette_p;
			currentBlending = BLEND;
		}
	}
}

// This function fills the palette with totally random colors.
void Attract::SetupTotallyRandomPalette() {
	for (int i = 0; i < 16; i++) {
		currentPalette[i] = CHSV(random8(), 255, random8());
	}
}

// This function sets up a palette of black and white stripes,
// using code.  Since the palette is effectively an array of
// sixteen CRGB colors, the various fill_* functions can be used
// to set them up.
void Attract::SetupBlackAndWhiteStripedPalette() {
	// 'black out' all 16 palette entries...
	fill_solid(currentPalette, 16, CRGB::Black);
	// and set every fourth one to white.
	currentPalette[0] = CRGB::White;
	currentPalette[4] = CRGB::White;
	currentPalette[8] = CRGB::White;
	currentPalette[12] = CRGB::White;

}

// This function sets up a palette of purple and green stripes.
void Attract::SetupPurpleAndGreenPalette() {
	CRGB purple = CHSV(HUE_PURPLE, 255, 255);
	CRGB green = CHSV(HUE_GREEN, 255, 255);
	CRGB black = CRGB::Black;

	currentPalette = CRGBPalette16(green, green, black, black, purple, purple,
			black, black, green, green, black, black, purple, purple, black,
			black);
}

// This example shows how to set up a static color palette
// which is stored in PROGMEM (flash), which is almost always more
// plentiful than RAM.  A static PROGMEM palette like this
// takes up 64 bytes of flash.
const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM = { CRGB::Red,
		CRGB::Gray, // 'white' is too bright compared to red and blue
		CRGB::Blue, CRGB::Black,

		CRGB::Red, CRGB::Gray, CRGB::Blue, CRGB::Black,

		CRGB::Red, CRGB::Red, CRGB::Gray, CRGB::Gray, CRGB::Blue, CRGB::Blue,
		CRGB::Black, CRGB::Black };

// Additionl notes on FastLED compact palettes:
//
// Normally, in computer graphics, the palette (or "color lookup table")
// has 256 entries, each containing a specific 24-bit RGB color.  You can then
// index into the color palette using a simple 8-bit (one byte) value.
// A 256-entry color palette takes up 768 bytes of RAM, which on Arduino
// is quite possibly "too many" bytes.
//
// FastLED does offer traditional 256-element palettes, for setups that
// can afford the 768-byte cost in RAM.
//
// However, FastLED also offers a compact alternative.  FastLED offers
// palettes that store 16 distinct entries, but can be accessed AS IF
// they actually have 256 entries; this is accomplished by interpolating
// between the 16 explicit entries to create fifteen intermediate palette
// entries between each pair.
//
// So for example, if you set the first two explicit entries of a compact
// palette to Green (0,255,0) and Blue (0,0,255), and then retrieved
// the first sixteen entries from the virtual palette (of 256), you'd get
// Green, followed by a smooth gradient from green-to-blue, and then Blue.

