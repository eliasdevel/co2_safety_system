/*
 * Software for home brew beer at home using LCD shild, ds18b20 temperature sensor
 * Libs :
 * https://github.com/milesburton/Arduino-Temperature-Control-Library
 *
 */

#include "LcdHelper.h"
#include "Menu.h"
// #include <EEPROM.h>

const long intervalBuzzerAlarm = 500;

int currentRampa = 0;
int minutesRightTemperature = 0;
int minutesAux = 0;

byte eeprom_time_positions[4] = {1, 3, 5, 7};
byte eeprom_temperature_positions[4] = {0, 2, 4, 6};



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
  btnPush = readKeypad();

  mainMenuBtn();

  if (btnPush == 'S') // enter selected menu
  {
    waitBtnRelease();
    switch (mainMenuPage)
    {
    case 1:
      config();
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

  if (btnPush != 'N')
  {
    count = 0;
  }
  else
  {
    count++;
  }
  delay(10);

} //--------------- End of loop() loop ---------------------
void config()
{
  insideMenu(1);
}

void co2Rule()
{
  lcd.setCursor(0, 0);
  lcd.write(byte(1));
  lcd.print(1000);
  lcd.write(byte(0));
  lcd.print("C");
}
