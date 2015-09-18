/*
 * BallStore.h
 *
 *  Created on: 28.08.2015
 *      Author: sr
 */

#ifndef PINBALL_LW3_BALLSTORE_H_
#define PINBALL_LW3_BALLSTORE_H_

#include "SwitchAction.h"

class BallStore : public SwitchAction {
public:
	BallStore(int maxBalls);
	virtual ~BallStore();

	virtual void onSwitchUpdate(bool active, int num);

	int getBalls() const {
		return balls;
	}

private:
	int lastIndex;
	int* switchVal;
	int* switchIndex;

	int balls;
	int maxBalls;

};

#endif /* PINBALL_LW3_BALLSTORE_H_ */
