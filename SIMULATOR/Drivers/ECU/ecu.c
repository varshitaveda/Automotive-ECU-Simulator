/*
 * ecu.c
 *
 *  Created on: Jul 30, 2026
 *      Author: Veda Varshita A
 */
#include "ecu.h"
#include "vehicle.h"
#include<string.h>
static ECU_Fault_t FaultStatus;

static ECU_Ignition_t IgnitionState = ECU_IGNITION_OFF;

//void ECU_SetIgnition(ECU_Ignition_t state)
//{
//    IgnitionState = state;
//}
//
//ECU_Ignition_t ECU_GetIgnition(void)
//{
//    return IgnitionState;
//}

ECU_Fault_t ECU_GetFaultStatus(void)
{
    return FaultStatus;
}

void ECU_CheckFaults(void)
{
    /* Temperature */

    if(VehicleData.temperature > 32)
    {
        FaultStatus.overTemperature = 1;
    }
    else
    {
        FaultStatus.overTemperature = 0;
    }


    /* Fuel */

    if(VehicleData.fuel < 15)
    {
        FaultStatus.lowFuel = 1;
    }
    else
    {
        FaultStatus.lowFuel = 0;
    }


    /* Speed */

    if(VehicleData.speed > 120)
    {
        FaultStatus.overSpeed = 1;
    }
    else
    {
        FaultStatus.overSpeed = 0;
    }


    /* RPM */

    if(VehicleData.rpm > 5500)
    {
        FaultStatus.overRPM = 1;
    }
    else
    {
        FaultStatus.overRPM = 0;
    }
}


