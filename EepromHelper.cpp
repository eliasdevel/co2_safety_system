#include "EepromHelper.h"

void saveMaxPPM(int ppm)
{
    EEPROM.begin();
    unsigned int addr1 = 0;
    unsigned int addr2 = 0;

    byte a = ppm;

    byte b = ppm >> 8;

    EEPROM.write(ppmAddr01, a);
    EEPROM.write(ppmAddr02, b);
    EEPROM.end();
}
void eepromSetup()
{
    EEPROM.begin();
}
int loadMaxPPM()
{
    EEPROM.begin();
    byte a = EEPROM.read(ppmAddr01);
    byte b = EEPROM.read(ppmAddr02);
    // get bytes to int
    unsigned int x = (b << 8) | a;
    EEPROM.end();
    return x;
}