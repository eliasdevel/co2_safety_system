#ifndef MENU
#define MENU
#include <Arduino.h>
#include "LcdHelper.h"
#include "EepromHelper.h"
void mainMenuBtn();
void mainMenuDisplay();
void insideMenu(int menuNumber);
extern char btnPush;
extern byte mainMenuPage;
extern byte mainMenuTotal;
extern byte mainMenuPageOld;
#endif