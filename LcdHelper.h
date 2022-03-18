
#ifndef LCD_INIT
#define LCD_INIT
#include <Arduino.h>
#include <LiquidCrystal.h>
void lcdSetup();

extern LiquidCrystal lcd;

extern const int keypadPin;
char readKeypad();
extern int keypadValue;
void waitBtnRelease();
void mainMenuBtn();
// int keypad_value_old = 0;
// int buzzerState = LOW;
// int currentRampa = 0;
// int minutesRightTemperature = 0;
// int minutesAux = 0;
#endif
