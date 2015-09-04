/*
 * Attract.h
 *
 *  Created on: 31.08.2015
 *      Author: sr
 */

#ifndef PINBALL_LW3_ATTRACT_H_
#define PINBALL_LW3_ATTRACT_H_

#include "Effect.h"

class Attract : public Effect {
public:
	Attract(int* index, int num, int animationSpeed);
	virtual ~Attract(){};

	virtual void updateLeds( unsigned long now, CRGB* leds );

	void ChangePalettePeriodically();
	void SetupBlackAndWhiteStripedPalette();
	void SetupPurpleAndGreenPalette();
	void SetupTotallyRandomPalette();

	CRGBPalette16 currentPalette;
	TBlendType currentBlending;
	uint8_t startIndex;
	int animationDelay;
	uint32_t nextUpdate;
};

#endif /* PINBALL_LW3_ATTRACT_H_ */
