
#ifndef IO_CONTROL
#define IO_CONTROL
#include <Arduino.h>
#define outputPin1 2
#define outputPin2 3
#define outputPin3 11
#define outputPin4 12

void setupIoControl();
void ioLogic(int currentPPM, int maxPPM);
void setOutputs(byte mode);
#endif