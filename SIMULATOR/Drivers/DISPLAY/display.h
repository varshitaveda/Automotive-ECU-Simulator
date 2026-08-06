/*
 * display.h
 *
 *  Created on: Jul 30, 2026
 *      Author: Veda Varshita A
 */

#ifndef DISPLAY_H
#define DISPLAY_H

#include "vehicle.h"
#include "ecu.h"
#include "main.h"

void Display_Update(VehicleData_t *data, ECU_Fault_t *fault);

void Display_IgnitionOff(void);
void Display_IgnitionOn(void);

#endif /* DISPLAY_DISPLAY_H_ */
