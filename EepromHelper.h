#ifndef EEPROM_HELPER
#define EEPROM_HELPER

#define ppmAddr01 0x01
#define ppmAddr02 0x02

#include <Arduino.h>
#include <EEPROM.h>

void saveMaxPPM(int ppm);
void eepromSetup();
int loadMaxPPM();

#endif