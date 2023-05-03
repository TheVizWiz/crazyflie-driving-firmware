
#include "deck.h"
#include "param.h"
#include "deck_analog.h"

#define NO_DRIVE 0
#define FORWARD_DRIVE 1
#define BACKWARD_DRIVE 2
#define LEFT_TURN 3
#define RIGHT_TURN 4

#define LEFT_0 DECK_GPIO_IO3
#define LEFT_1 DECK_GPIO_IO4
#define RIGHT_0 DECK_GPIO_IO1
#define RIGHT_1 DECK_GPIO_IO2

static bool isInitialized = false;

static char driveMode = 0;

void initDriverBase(DeckInfo *info) {
    pinMode(LEFT_0, OUTPUT);
    pinMode(LEFT_1, OUTPUT);
    pinMode(RIGHT_0, OUTPUT);
    pinMode(RIGHT_1, OUTPUT);
    isInitialized = true;
}

void drive () {

	switch (driveMode) {
		case FORWARD_DRIVE:
			digitalWrite(LEFT_0, LOW);
			digitalWrite(LEFT_1, HIGH);
			digitalWrite(RIGHT_0, LOW);
			digitalWrite(RIGHT_1, HIGH);
			break;
		case BACKWARD_DRIVE:
			digitalWrite(LEFT_0, HIGH);
			digitalWrite(LEFT_1, LOW);
			digitalWrite(RIGHT_0, HIGH);
			digitalWrite(RIGHT_1, LOW);
			break;
		case LEFT_TURN:
			digitalWrite(LEFT_0, HIGH);
			digitalWrite(LEFT_1, LOW);
			digitalWrite(RIGHT_0, LOW);
			digitalWrite(RIGHT_1, HIGH);
			break;
		case RIGHT_TURN:
			digitalWrite(LEFT_0, LOW);
			digitalWrite(LEFT_1, HIGH);
			digitalWrite(RIGHT_0, HIGH);
			digitalWrite(RIGHT_1, LOW);
		default:
			digitalWrite(LEFT_0, LOW);
			digitalWrite(LEFT_1, LOW);
			digitalWrite(RIGHT_0, LOW);
			digitalWrite(RIGHT_1, LOW);
	}
}



const DeckDriver driveBaseDriver = {
  .vid = 0,
  .pid = 0,
  .name = "driveBase",
  .usedGpio = DECK_USING_IO_1 | DECK_USING_IO_2 | DECK_USING_IO_3 | DECK_USING_IO_4,

  .init = initDriverBase,
};

DECK_DRIVER(driveBaseDriver);

PARAM_GROUP_START(deck)
PARAM_ADD_WITH_CALLBACK(PARAM_UINT8, driveMode, &driveMode, &drive)
PARAM_GROUP_STOP(deck)