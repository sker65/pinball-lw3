/*
 * SlingFlash.h
 *
 *  Created on: 31.08.2015
 *      Author: sr
 */

#ifndef PINBALL_LW3_SLINGFLASH_H_
#define PINBALL_LW3_SLINGFLASH_H_

#include "SwitchAction.h"

#include "Effect.h"

class SlingFlash : public SwitchAction {
public:
	SlingFlash(Effect* effect);
	virtual ~SlingFlash();

	virtual void onSwitchUpdate(bool active, int num);
private:
	Effect* effect;
};

#endif /* PINBALL_LW3_SLINGFLASH_H_ */
