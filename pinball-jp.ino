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

int slingRightLeds[] = { 50, 51 };
int slingLeftLeds[] = { 54, 55 };

BallStore ballStore(3);

CRGB white(255, 255, 255);
//CRGB warmWhite100( 255, 214, 170);

Flash slingRightFlash(500, &white, slingRightLeds, 2, 1);
Flash slingLeftFlash(500, &white, slingLeftLeds, 2, 1);

SlingFlash slingRight(&slingRightFlash);
SlingFlash slingLeft(&slingLeftFlash);

const int allLeds[] = { // von unten nach oben
		0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,
		17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,
		34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,
		51,52,53,54,55,56,57,58,59,60,61
};

const int allPlayFieldLeds[] = { // von unten nach oben
		37,38,39,40,41,42,43,44,45,46,47,48,49,50,
		51,52,53,54,55,56,57,58,59,60,61
};

const int rightSpeaker[] = {
		0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16
};

const int leftSpeaker[] = {
		17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33
};

const int topper[] = {
		34,35,36
};

#define ALL_LEDS 38
#define GI_SENSE_PIN 8

Attract attract(allLeds, ALL_LEDS, 20);  // array of led index, num, updates per sec

NormalPlay normalPlay(allLeds, ALL_LEDS, 20, 40, GI_SENSE_PIN);

MultiBallPlay multiBallPlay(allLeds, ALL_LEDS, 20);

LedDriver ledDriver(40);

// synchronization between interrupt routines and FASTLED.show() needed
// switch callback also on a regular basis, not only edge
// maybe do the FASTLED.show() always at the end of a scan cycle when Timer1 stops

void setup() {
	DDRA = 0; // all PORTA is input
	Serial.begin(9600);

	//Timer1.initialize(933);
	//Timer1.stop();
	//Timer1.attachInterrupt(readSwitches); // blinkLED to run every 0.15 seconds

	// int 0 refers to digital pin 2 see here
	// https://www.arduino.cc/en/Reference/AttachInterrupt

	//attachInterrupt(0, colStrobe, FALLING);

	pinMode(12, OUTPUT); // LED
	//pinMode(30, OUTPUT); // Port B7 for control wave output

	pinMode(GI_SENSE_PIN, INPUT_PULLUP);

	// register ball store for 3 switches
	//switchScanner.registerSwitchAction(1,3, &ballStore, PERIODIC);
	//switchScanner.registerSwitchAction(1,2, &ballStore, PERIODIC);
	//switchScanner.registerSwitchAction(1,5, &ballStore, PERIODIC);

//	ledDriver.registerEffect(&attract);
	ledDriver.registerEffect(&normalPlay);
	//ledDriver.registerEffect(&multiBallPlay);
	//ledDriver.registerEffect(&slingLeftFlash);
	//ledDriver.registerEffect(&slingRightFlash);

	//switchScanner.registerSwitchAction(4,4,&slingRight, EDGE);
	//switchScanner.registerSwitchAction(3,4,&slingLeft, EDGE);

	// this is active by default
	normalPlay.active = true;

}


void loop() {
	uint32_t now = millis();
	//switchScanner.update(now);
	ledDriver.update(now);
/*	switch(ballStore.getBalls() ) {
	case 3:
		attract.active = true;
		normalPlay.active = false;
		multiBallPlay.active = false;
		break;
	case 2:
		attract.active = false;
		normalPlay.active = true;
		multiBallPlay.active = false;
		break;
	case 1:
	case 0:
		attract.active = false;
		normalPlay.active = false;
		multiBallPlay.active = true;
		break;
	}*/
}
