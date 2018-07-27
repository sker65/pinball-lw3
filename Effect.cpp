/*
 * Effect.cpp
 *
 *  Created on: 31.08.2015
 *      Author: sr
 */

#include "Effect.h"

Effect::Effect(int level, const int* index, int num) {
	this->level = level;
	this->startTime = 0L;
	this->index = index;
	this->num = num;
}

Effect::~Effect() {
	// TODO Auto-generated destructor stub
}

