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
    lcd.print("Config");
    break;
  case 2:
    lcd.print("Monitor");
  }
}

void insideMenu(int menuNumber)
{

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("R" + String(menuNumber) + ", Temp:");

  lcd.setCursor(0, 1);
  lcd.print("* Tempo:");
  lcd.setCursor(0, 1);

  int temperature = 0;
  int timing = 0;
  int idr1 = 0;
  while (readKeypad() != 'L')
  {
    lcd.blink();

    if (idr1 == 0)
    {
      lcd.setCursor(10, 0);
      if (readKeypad() == 'U')
      {
        delay(100);
        temperature++;
      }
      if (readKeypad() == 'D')
      {
        delay(100);
        temperature--;
      }

      lcd.print(temperature);
      lcd.print("*C");
    }
    if (idr1 == 1)
    {
      if (readKeypad() == 'U')
      {
        delay(100);
        timing++;
      }
      if (readKeypad() == 'D')
      {
        delay(100);
        timing--;
      }
      lcd.setCursor(8, 1);

      lcd.print(timing);
      lcd.print("m");
    }
    if (readKeypad() == 'R')
    {
      delay(500);
      idr1++;
    }

    if (idr1 != 1 && idr1 != 0)
      idr1 == 0;
  }

//   EEPROM.write(eeprom_temperature_positions[menuNumber - 1], temperature);
//   EEPROM.write(eeprom_time_positions[menuNumber - 1], timing);
}