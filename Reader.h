#ifndef READER
#define READER
#include <Arduino.h>
#include <MQUnifiedsensor.h>

#define placa "Arduino UNO"
#define Voltage_Resolution 5
#define pin A1 //Analog input 0 of your arduino
#define type "MQ-135" //MQ135
#define ADC_Bit_Resolution 10 // For arduino UNO/MEGA/NANO
#define RatioMQ135CleanAir 3.6

extern MQUnifiedsensor MQ135;
float readCo2();

void co2SensorSetup();
#endif