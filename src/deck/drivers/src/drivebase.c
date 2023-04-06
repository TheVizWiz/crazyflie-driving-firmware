
#include "deck.h"



void initDriverBase(DeckInfo *info) {
    pinMode(DECK_GPIO_IO1, OUTPUT);
    pinMode(DECK_GPIO_IO2, OUTPUT);
}




const DeckDriver driveBaseDriver = {
  .vid = 0,
  .pid = 0,
  .name = "driveBase",
  .usedGpio = DECK_USING_IO_1 | DECK_USING_IO_2,

  .init = myledInit,
  .test = myledTest,

};

DECK_DRIVER(driveBaseDriver);