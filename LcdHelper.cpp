#include "LcdHelper.h"

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void lcdSetup()
{
  lcd.begin(16, 2); // Initialize a 2x16 type LCD
  uint8_t circle[8] = {0x2, 0x5, 0x2, 0x0, 0x0, 0x0, 0x0};
  uint8_t temp[8] = {0x4, 0xa, 0xa, 0xa, 0xe, 0xa, 0x4};
  uint8_t clock[8] = {0x0, 0xe, 0x11, 0x15, 0x13, 0xe, 0x0};
  lcd.createChar(0, circle);
  lcd.createChar(1, temp);
  lcd.createChar(2, clock);
}
const int keypadPin = A0;
int keypadValue = 0;
// keypad_pin = A0;

char readKeypad()
{
  /* Keypad button analog Value
  no button pressed 1023
  select  741
  left    503
  down    326
  up      142
  right   0
  */
  keypadValue = analogRead(keypadPin);

  if (keypadValue < 100)
    return 'R';
  else if (keypadValue < 200)
    return 'U';
  else if (keypadValue < 400)
    return 'D';
  else if (keypadValue < 600)
    return 'L';
  else if (keypadValue < 800)
    return 'S';
  else
    return 'N';
}

void waitBtnRelease()
{
  while (analogRead(keypadPin) < 800)
  {
  }
}

void displayCo2(int val)
{
  lcd.noBlink();
  lcd.setCursor(0, 0);
  // lcd.write(byte(1));
  lcd.print(val);
  // lcd.write(byte(0));
  lcd.print("PPM");
}
