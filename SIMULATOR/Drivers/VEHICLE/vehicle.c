/*
 * vehicle.c
 *
 *  Created on: Jul 30, 2026
 *      Author: Veda Varshita A
 */

#include "vehicle.h"

/* Global vehicle data */
VehicleData_t VehicleData;

/* Temperature: LM35 */
uint8_t Vehicle_GetTemperature(uint32_t adcValue)
{
    float voltage = (adcValue * 3.3f) / 4095.0f;
    return (uint8_t)(voltage * 100.0f);
}

/* Speed: Potentiometer -> 0 to 180 km/h */
uint16_t Vehicle_GetSpeed(uint32_t adcValue)
{
    return (adcValue * 180U) / 4095U;
}

/* Fuel: Software simulation */
uint8_t Vehicle_GetFuel(uint16_t speed)
{
    static float fuelLevel = 100.0f;

    fuelLevel -= (speed * 0.001f);

    if(fuelLevel < 0)
        fuelLevel = 0;

    return (uint8_t)fuelLevel;
}

/* RPM: Hall sensor value */
uint16_t Vehicle_GetRPM(uint32_t adcValue)
{
    return (adcValue * 6000) / 4095;
}
