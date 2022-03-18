/*
 * Software for home brew beer at home using LCD shild, ds18b20 temperature sensor
 * Libs :
 * https://github.com/milesburton/Arduino-Temperature-Control-Library
 *
 */

#include "LcdHelper.h"
#include <EEPROM.h>

const long intervalBuzzerAlarm = 500;

int currentRampa = 0;
int minutesRightTemperature = 0;
int minutesAux = 0;

byte eeprom_time_positions[4] = {1, 3, 5, 7};
byte eeprom_temperature_positions[4] = {0, 2, 4, 6};

char btn_push;

byte mainMenuPage = 1;
byte mainMenuPageOld = 1;
byte mainMenuTotal = 2;

void setup()
{

  // for (int i = 0; i <= 255; i++)
  // {
  //   if (EEPROM.read(i) == 255)
  //   {
  //     EEPROM.write(i, 0);
  //   }
  // }

  lcdSetup();
  mainMenuDisplay();
  delay(1000);
}
int count = 0;
void loop()
{
  lcd.noBlink();
  btn_push = readKeypad();

  mainMenuBtn();

  if (btn_push == 'S') // enter selected menu
  {
    waitBtnRelease();
    switch (mainMenuPage)
    {
    case 1:
      Config();
      break;
    case 2:

      break;
    }

    mainMenuDisplay();
    waitBtnRelease();
  }

  if (count >= 100)
  {
    count = 99;
    lcd.clear();
    co2Rule();
  }

  if (btn_push != 'N')
  {
    count = 0;
  }
  else
  {
    count++;
  }
  delay(10);

} //--------------- End of loop() loop ---------------------
void Config()
{
  insideMenu(1);
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

void mainMenuBtn()
{
  waitBtnRelease();
  if (btn_push == 'U')
  {
    mainMenuPage++;
    if (mainMenuPage > mainMenuTotal)
      mainMenuPage = 1;
  }
  else if (btn_push == 'D')
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

void insideMenu(int menuNumber)
{

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("R" + String(menuNumber) + ", Temp:");

  lcd.setCursor(0, 1);
  lcd.print("* Tempo:");
  lcd.setCursor(0, 1);

  int temperature = EEPROM.read(eeprom_temperature_positions[menuNumber - 1]);
  int timing = EEPROM.read(eeprom_time_positions[menuNumber - 1]);
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

  EEPROM.write(eeprom_temperature_positions[menuNumber - 1], temperature);
  EEPROM.write(eeprom_time_positions[menuNumber - 1], timing);
}



void co2Rule()
{
  lcd.setCursor(0, 0);
  lcd.write(byte(1));
  lcd.print(1000);
  lcd.write(byte(0));
  lcd.print("C");
}
