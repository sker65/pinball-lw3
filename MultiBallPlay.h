/*
 * MultiBallPlay.h
 *
 *  Created on: 04.09.2015
 *      Author: sr
 */

#ifndef MULTIBALLPLAY_H_
#define MULTIBALLPLAY_H_
#include "Effect.h"

class MultiBallPlay : public Effect {
public:
	MultiBallPlay(const int* index, int num, int animationSpeed);
	virtual ~MultiBallPlay(){};
	virtual void updateLeds( unsigned long now, CRGB* leds );

	void SetupBlackAndWhiteStripedPalette();

	uint8_t paletteIndex;
	int animationDelay;
	uint32_t nextUpdate;
	CRGBPalette16 pal;
};

#endif /* MULTIBALLPLAY_H_ */
