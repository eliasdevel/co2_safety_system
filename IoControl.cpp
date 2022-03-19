
#include "IoControl.h"

void setupIoControl()
{
    pinMode(outputPin1, OUTPUT);
    pinMode(outputPin2, OUTPUT);
    pinMode(outputPin3, OUTPUT);
    pinMode(outputPin4, OUTPUT);
    setOutputs(LOW);
}

void setOutputs(byte mode)
{
    digitalWrite(outputPin1, mode);
    digitalWrite(outputPin2, mode);
    digitalWrite(outputPin3, mode);
    digitalWrite(outputPin4, mode);
}

void ioLogic(int currentPPM, int maxPPM)
{
    if (currentPPM >= maxPPM)
    {
        setOutputs(HIGH);
    }
    else
    {
        setOutputs(LOW);
    }
}
