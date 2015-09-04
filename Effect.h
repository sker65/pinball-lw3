/*
 * Effect.h
 *
 *  Created on: 31.08.2015
 *      Author: sr
 */

#ifndef PINBALL_LW3_EFFECT_H_
#define PINBALL_LW3_EFFECT_H_

#include <FastLED.h>

class Effect {
public:
	Effect(int level, int* index, int num);
	virtual ~Effect();

	virtual void updateLeds( unsigned long now, CRGB* leds ) = 0;
	virtual void start() { startTime = millis(); active = true; }

	int level;
	uint32_t startTime;
	bool active = false;
	int* index;
	int num;
};

#endif /* PINBALL_LW3_EFFECT_H_ */
