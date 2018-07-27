/*
 * Flash.h
 *
 *  Created on: 31.08.2015
 *      Author: sr
 */

#ifndef PINBALL_LW3_FLASH_H_
#define PINBALL_LW3_FLASH_H_

#include "Effect.h"

class Flash : public Effect {
public:
	Flash(int duration, CRGB* color, const int* pos, int num, int level);
	virtual ~Flash();

	virtual void updateLeds( unsigned long now, CRGB* leds );

private:
	int duration;
	CRGB* color;
};

#endif /* PINBALL_LW3_FLASH_H_ */
