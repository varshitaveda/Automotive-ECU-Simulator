/*
 * ignition.h
 *
 *  Created on: Jul 31, 2026
 *      Author: Veda Varshita A
 */

#ifndef IGNITION_H
#define IGNITION_H

#include <stdint.h>

typedef enum
{
    IGNITION_OFF = 0,
    IGNITION_ON
} IgnitionState_t;

void Ignition_Init(void);
void Ignition_Update(void);
IgnitionState_t Ignition_GetState(void);

#endif /* IGNITION_IGNITION_H_ */
