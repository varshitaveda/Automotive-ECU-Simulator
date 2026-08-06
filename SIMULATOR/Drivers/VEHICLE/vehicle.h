/*
 * vehicle.h
 *
 *  Created on: Jul 30, 2026
 *      Author: Veda Varshita A
 */

#ifndef VEHICLE_H
#define VEHICLE_H

#include <stdint.h>

typedef struct
{
    uint32_t tempADC;
    uint32_t fuelADC;
    uint32_t speedADC;
    uint32_t rpmADC;

    uint8_t temperature;
    uint8_t fuel;

    uint16_t speed;
    uint16_t rpm;

}VehicleData_t;

extern VehicleData_t VehicleData;

uint8_t Vehicle_GetTemperature(uint32_t adcValue);
uint16_t Vehicle_GetSpeed(uint32_t adcValue);
uint8_t Vehicle_GetFuel(uint16_t speed);
uint16_t Vehicle_GetRPM(uint32_t rpmValue);

#endif /* VEHICLE_VEHICLE_H_ */
