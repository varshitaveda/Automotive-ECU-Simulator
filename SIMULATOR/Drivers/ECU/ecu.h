/*
 * ecu.h
 *
 *  Created on: Jul 30, 2026
 *      Author: Veda Varshita A
 */

#ifndef ECU_H
#define ECU_H

#include <stdint.h>

typedef struct
{
    uint8_t overTemperature;

    uint8_t lowFuel;

    uint8_t overSpeed;

    uint8_t overRPM;

}ECU_Fault_t;


typedef enum
{
    ECU_IGNITION_OFF = 0,

    ECU_IGNITION_ON

}ECU_Ignition_t;


/* APIs */

void ECU_CheckFaults(void);

//void ECU_SetIgnition(ECU_Ignition_t state);

//ECU_Ignition_t ECU_GetIgnition(void);

ECU_Fault_t ECU_GetFaultStatus(void);


#endif /* ECU_ECU_H_ */
