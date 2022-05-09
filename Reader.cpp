#include "Reader.h"

MQUnifiedsensor MQ135(placa, Voltage_Resolution, ADC_Bit_Resolution, pin, type);

float readCo2()
{
    MQ135.update();
    MQ135.setA(605.18);
    MQ135.setB(-3.937);            // Configurate the ecuation values to get CO concentration
    float CO = MQ135.readSensor(); // Sensor will read PPM concentration using the model and a and b values setted before or in the setup

    MQ135.setA(77.255);
    MQ135.setB(-3.18);                  // Configurate the ecuation values to get Alcohol concentration
    float Alcohol = MQ135.readSensor(); // Sensor will read PPM concentration using the model and a and b values setted before or in the setup

    MQ135.setA(110.47);
    MQ135.setB(-2.862);             // Configurate the ecuation values to get CO2 concentration
    float CO2 = MQ135.readSensor(); // Sensor will read PPM concentration using the model and a and b values setted before or in the setup
    CO2 = (CO2 * 100) + 400;
    MQ135.setA(44.947);
    MQ135.setB(-3.445);                 // Configurate the ecuation values to get Tolueno concentration
    float Tolueno = MQ135.readSensor(); // Sensor will read PPM concentration using the model and a and b values setted before or in the setup

    MQ135.setA(102.2);
    MQ135.setB(-2.473);             // Configurate the ecuation values to get NH4 concentration
    float NH4 = MQ135.readSensor(); // Sensor will read PPM concentration using the model and a and b values setted before or in the setup

    MQ135.setA(34.668);
    MQ135.setB(-3.369);                 // Configurate the ecuation values to get Acetona concentration
    float Acetona = MQ135.readSensor(); //
    Serial.println("co2:" + String(CO2, 2));

    return CO2;
}

void co2SensorSetup()
{

    // Set math model to calculate the PPM concentration and the value of constants
    MQ135.setRegressionMethod(1); //_PPM =  a*ratio^b

    /*****************************  MQ Init ********************************************/
    // Remarks: Configure the pin of arduino as input.
    /************************************************************************************/
    MQ135.init();
    Serial.print("Calibrating please wait.");
    float calcR0 = 0;
    for (int i = 1; i <= 10; i++)
    {
        MQ135.update(); // Update data, the arduino will be read the voltage on the analog pin
        calcR0 += MQ135.calibrate(RatioMQ135CleanAir);
        Serial.print(".");
    }

    MQ135.setR0(calcR0 / 10);
    Serial.println("  done!.");

    if (isinf(calcR0))
    {
        Serial.println("Warning: Conection issue founded, R0 is infite (Open circuit detected) please check your wiring and supply");
        while (1)
            ;
    }
    if (calcR0 == 0)
    {
        Serial.println("Warning: Conection issue founded, R0 is zero (Analog pin with short circuit to ground) please check your wiring and supply");
        while (1)
            ;
    }
    /*****************************  MQ CAlibration ********************************************/
    Serial.println("** Lectures from MQ-135 ****");
    Serial.println("|    CO   |  Alcohol |   CO2  |  Tolueno  |  NH4  |  Acteona  |");
}