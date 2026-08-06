/*
 * led.h
 *
 *  Created on: Jul 31, 2026
 *      Author: Veda Varshita A
 */

#ifndef LED_H
#define LED_H

#include <stdint.h>
#include "ecu.h"
/* RGB LED Colors */

typedef enum
{
    LED_OFF = 0,
    LED_RED,
    LED_GREEN,
    LED_BLUE,
    LED_YELLOW,
    LED_PURPLE,
    LED_CYAN,
    LED_WHITE

}LED_Color_t;


/* APIs */

void LED_Init(void);

void LED_SetColor(LED_Color_t color);

void BUTTON_Init(void);

uint8_t BUTTON_IsPressed(void);

void LED_Update(ECU_Fault_t fault);

#endif /* LED_LED_H_ */
