#include <TimerOne.h>
#include "BallStore.h"
#include "Flash.h"
#include "Attract.h"
#include "NormalPlay.h"
#include "MultiBallPlay.h"
#include "LedDriver.h"
#include "SlingFlash.h"
#include "SwitchScanner.h"
#include <FastLED.h>


SwitchScanner switchScanner(300);

// this will called as interrupt triggered by falling edge on pin 2
void colStrobe() {
	if( !switchScanner.getSwitchChanged() ) {
		// as the hole col strobe is ca 933 us long, we start the timer right in the middle
		delayMicroseconds(450);
		Timer1.start();
	}
}

void readSwitches() {
	switchScanner.readSwitches();
}

int slingRightLeds[] = { 34, 35 };
int slingLeftLeds[] = { 30, 31 };

BallStore ballStore(3);

CRGB white(255, 255, 255);

Flash slingRightFlash(500, &white, slingRightLeds, 2, 1);
Flash slingLeftFlash(500, &white, slingLeftLeds, 2, 1);

SlingFlash slingRight(&slingRightFlash);
SlingFlash slingLeft(&slingLeftFlash);

int allLeds[] = { // von unten nach oben
		32,33,31,34,30,
		35,29,3,27,2,
		4,5,6,26,0,
		1,25,24,7,14,
		13,12,22,21,18,
		17,16,15,11,19,
		8,20,9 };

Attract attract(allLeds, 33, 20);  // array of led index, num, updates per sec
NormalPlay normalPlay(allLeds, 33, 20);
MultiBallPlay multiBallPlay(allLeds, 33, 20);

LedDriver ledDriver(40);

// synchronization between interrupt routines and FASTLED.show() needed
// switch callback also on a regular basis, not only edge
// maybe do the FASTLED.show() always at the end of a scan cycle when Timer1 stops

void setup() {
	DDRA = 0; // all PORTA is input
	Serial.begin(9600);

	Timer1.initialize(933);
	Timer1.stop();
	Timer1.attachInterrupt(readSwitches); // blinkLED to run every 0.15 seconds

	// int 0 refers to digital pin 2 see here
	// https://www.arduino.cc/en/Reference/AttachInterrupt

	attachInterrupt(0, colStrobe, FALLING);

	pinMode(13, OUTPUT); // LED
	pinMode(30, OUTPUT); // Port B7 for control wave output

	// register ball store for 3 switches
	switchScanner.registerSwitchAction(1,0, &ballStore, PERIODIC);
	switchScanner.registerSwitchAction(1,7, &ballStore, PERIODIC);
	switchScanner.registerSwitchAction(1,5, &ballStore, PERIODIC);

	ledDriver.registerEffect(&attract);
	ledDriver.registerEffect(&normalPlay);
	ledDriver.registerEffect(&multiBallPlay);
	ledDriver.registerEffect(&slingLeftFlash);
	ledDriver.registerEffect(&slingRightFlash);

	switchScanner.registerSwitchAction(4,2,&slingRight, EDGE);
	switchScanner.registerSwitchAction(3,2,&slingLeft, EDGE);

	// this is active by default
	attract.active = true;

}


void loop() {
	uint32_t now = millis();
	switchScanner.update(now);
	ledDriver.update(now);
	switch(ballStore.getBalls() ) {
	case 3:
		attract.active = true;
		normalPlay.active = false;
		multiBallPlay.active = false;
		break;
	case 2:
	case 1:
		attract.active = false;
		normalPlay.active = true;
		multiBallPlay.active = false;
		break;
	case 0:
		attract.active = false;
		normalPlay.active = false;
		multiBallPlay.active = true;
		break;
	}
}
