#ifndef EEPROM_HELPER
#define EEPROM_HELPER

#include <Arduino.h>

void saveMaxPPM(int ppm);
int loadMaxPPM();

#endif