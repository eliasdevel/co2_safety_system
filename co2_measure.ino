

#include "LcdHelper.h"
#include "Menu.h"
#include "Reader.h"
#include "IoControl.h"
#include "EepromHelper.h"
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
  setupIoControl();
  Serial.begin(9600);
  lcdSetup();
  co2SensorSetup();
  mainMenuDisplay();
  delay(1000);
}

int count = 0;
void loop()
{
  int ppm = (int) readCo2();
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

  if (count >= 20)
  {
    count = 19;
    lcd.clear();
    displayCo2(ppm);
  }

  if (btnPush != 'N')
  {
    count = 0;
  }
  else
  {
    count++;
  }
  delay(200);

  
  ioLogic(ppm, loadMaxPPM());
}
//--------------- End of loop() loop ---------------------
void config()
{
  insideMenu(1);
}
