
#include "IoControl.h"

void setupIoControl()
{
    pinMode(outputPin1, OUTPUT);
    pinMode(outputPin2, OUTPUT);
    pinMode(outputPin3, OUTPUT);
    pinMode(outputPin4, OUTPUT);
    setOutputs(HIGH);
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
        Serial.println("ios:hihg");
        // for this module low is active
        setOutputs(LOW);
    }
    else
    {
        Serial.println("ios:low");
        setOutputs(HIGH);
    }
}
