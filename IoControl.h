
#ifndef IO_CONTROL
#define IO_CONTROL
#include <Arduino.h>
#define outputPin1 3
#define outputPin2 4
#define outputPin3 5
#define outputPin4 6

void setupIoControl();
void ioLogic(int currentPPM, int maxPPM);
void setOutputs(byte mode);
#endif