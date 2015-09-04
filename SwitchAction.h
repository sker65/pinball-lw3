/*
 * SwitchAction.h
 *
 *  Created on: 12.11.2014
 *      Author: srinke
 */

#ifndef PINBALL_LW3_SWITCHACTION_H_
#define PINBALL_LW3_SWITCHACTION_H_

class SwitchAction {
public:
	virtual void onSwitchUpdate(bool active, int num) = 0;
};



#endif /* PINBALL_LW3_SWITCHACTION_H_ */
