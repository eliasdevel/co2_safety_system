

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

  Serial.begin(9600);
  lcdSetup();
  eepromSetup();
  co2SensorSetup();
  mainMenuDisplay();
  delay(1000);
  setupIoControl();
}

int loopLogicTimer = 0;

int count = 0;
void loop()
{
  int ppm = (int)readCo2();
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

  //A cada 4 segundos vai verificar
  if(loopLogicTimer >=20){
    ioLogic(ppm, loadMaxPPM());
    loopLogicTimer = 0;
  }
  

  loopLogicTimer++;
}
//--------------- End of loop() loop ---------------------
void config()
{
  insideMenu(1);
}
