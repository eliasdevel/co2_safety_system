

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
volatile int ppm = 0;
volatile int count = 0;
void setup()
{

  setupIoControl();
  Serial.begin(9600);
  lcdSetup();
  eepromSetup();
  co2SensorSetup();
  mainMenuDisplay();
  delay(1000);

  timersSetup(); // allows interrupts
}

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

  if (count >= 20)
  {
    count = 19;
    lcd.clear();
    displayCo2(ppm);
  }
}
ISR(TIMER0_COMPA_vect)
{ // timer0 interrupt 2kHz
}

ISR(TIMER1_COMPA_vect)
{ // timer1 interrupt 1Hz 
  // generates pulse wave of frequency 1Hz/2 = 0.5kHz (takes two cycles for full wave- toggle high then toggle low)
  ppm = (int)readCo2();
  ioLogic(ppm, loadMaxPPM());
  if (btnPush != 'N')
  {
    count = 0;
  }
  else
  {
    count++;
  }
}

ISR(TIMER2_COMPA_vect)
{ // timer1 interrupt 8kHz 
  // generates pulse wave of frequency 8kHz/2 = 4kHz (takes two cycles for full wave- toggle high then toggle low)
}

//--------------- End of loop() loop ---------------------
void config()
{
  insideMenu(1);
}

void timersSetup()
{
  cli(); // stop interrupts

  // set timer0 interrupt at 2kHz
  TCCR0A = 0; // set entire TCCR0A register to 0
  TCCR0B = 0; // same for TCCR0B
  TCNT0 = 0;  // initialize counter value to 0
  // set compare match register for 2khz increments
  OCR0A = 124; // = (16*10^6) / (2000*64) - 1 (must be <256)
  // turn on CTC mode
  TCCR0A |= (1 << WGM01);
  // Set CS01 and CS00 bits for 64 prescaler
  TCCR0B |= (1 << CS01) | (1 << CS00);
  // enable timer compare interrupt
  TIMSK0 |= (1 << OCIE0A);

  // set timer1 interrupt at 1Hz
  TCCR1A = 0; // set entire TCCR1A register to 0
  TCCR1B = 0; // same for TCCR1B
  TCNT1 = 0;  // initialize counter value to 0
  // set compare match register for 1hz increments
  OCR1A = 15624; // = (16*10^6) / (1*1024) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS10 and CS12 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);

  // set timer2 interrupt at 8kHz
  TCCR2A = 0; // set entire TCCR2A register to 0
  TCCR2B = 0; // same for TCCR2B
  TCNT2 = 0;  // initialize counter value to 0
  // set compare match register for 8khz increments
  OCR2A = 249; // = (16*10^6) / (8000*8) - 1 (must be <256)
  // turn on CTC mode
  TCCR2A |= (1 << WGM21);
  // Set CS21 bit for 8 prescaler
  TCCR2B |= (1 << CS21);
  // enable timer compare interrupt
  TIMSK2 |= (1 << OCIE2A);

  sei(); // allow interrupts
}