/*
 * NormalPlay.h
 *
 *  Created on: 04.09.2015
 *      Author: sr
 */

#ifndef NORMALPLAY_H_
#define NORMALPLAY_H_
#include "Effect.h"

class NormalPlay : public Effect {
public:
	NormalPlay(const int* index, int num, int animationSpeed, int holdCycles, int giSense);
	virtual ~NormalPlay(){};

	virtual void updateLeds( unsigned long now, CRGB* leds );

	uint8_t paletteIndex;
	int holdCycles;
	int cycle;
	int animationDelay;
	uint32_t nextUpdate;
	int giSense;
};

#endif /* NORMALPLAY_H_ */
