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
	NormalPlay(int* index, int num, int animationSpeed);
	virtual ~NormalPlay(){};

	virtual void updateLeds( unsigned long now, CRGB* leds );

	uint8_t paletteIndex;
	int animationDelay;
	uint32_t nextUpdate;
};

#endif /* NORMALPLAY_H_ */
