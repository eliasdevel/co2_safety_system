#include "Menu.h"
byte mainMenuPage = 1;
byte mainMenuTotal = 2;
byte mainMenuPageOld = 1;
char btnPush;

void mainMenuBtn()
{
  waitBtnRelease();
  if (btnPush == 'U')
  {
    mainMenuPage++;
    if (mainMenuPage > mainMenuTotal)
      mainMenuPage = 1;
  }
  else if (btnPush == 'D')
  {
    mainMenuPage--;
    if (mainMenuPage == 0)
      mainMenuPage = mainMenuTotal;
  }

  if (mainMenuPage != mainMenuPageOld) // only update display when page change
  {
    mainMenuDisplay();
    mainMenuPageOld = mainMenuPage;
  }
}

void mainMenuDisplay()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  switch (mainMenuPage)
  {
  case 1:
    lcd.print("Config Saida 1");
    break;
  case 2:
    lcd.print("Config saida 2");
  }
}

void insideMenu(int menuNumber)
{

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Saida" + String(menuNumber));

  lcd.setCursor(0, 1);
  lcd.print("Limite Aceitavel");
  lcd.setCursor(0, 1);

  int ppmSet = loadMaxPPM();
  int timing = 0;
  int idr1 = 0;
  while (readKeypad() != 'L')
  {
    lcd.blink();

    lcd.setCursor(7, 0);
    if (readKeypad() == 'U')
    {
      delay(10);
      ppmSet++;
    }
    if (readKeypad() == 'D')
    {
      delay(10);
      ppmSet--;
    }

    lcd.print(ppmSet);
    lcd.print("_PPM");
  }
  saveMaxPPM(ppmSet);
  //   EEPROM.write(eeprom_temperature_positions[menuNumber - 1], temperature);
  //   EEPROM.write(eeprom_time_positions[menuNumber - 1], timing);
}