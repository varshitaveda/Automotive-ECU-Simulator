/*
 * ignition.c
 *
 *  Created on: Jul 31, 2026
 *      Author: Veda Varshita A
 */
#include "ignition.h"
#include "gpio.h"

static IgnitionState_t IgnitionState = IGNITION_OFF;

void Ignition_Init(void)
{
    IgnitionState = IGNITION_OFF;
}

void Ignition_Update(void)
{
    static uint8_t previousState = 1;

    uint8_t currentState =
        GPIO_ReadPin(GPIO_PORT_C, GPIO_DRV_PIN_13);

    if((previousState == 1) && (currentState == 0))
    {
        if(IgnitionState == IGNITION_OFF)
            IgnitionState = IGNITION_ON;
        else
            IgnitionState = IGNITION_OFF;
    }

    previousState = currentState;
}

IgnitionState_t Ignition_GetState(void)
{
    return IgnitionState;
}
