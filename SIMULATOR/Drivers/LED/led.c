
/*
 * led.c
 *
 *  Created on: Jul 31, 2026
 *      Author: Veda Varshita A
 */
#include "led.h"
#include "gpio.h"

/* RGB LED pins */

#define LED_PORT        GPIO_PORT_B

#define RED_PIN         GPIO_DRV_PIN_3
#define GREEN_PIN       GPIO_DRV_PIN_4
#define BLUE_PIN        GPIO_DRV_PIN_5


/* Push button */

#define BUTTON_PORT     GPIO_PORT_C
#define BUTTON_PIN      GPIO_DRV_PIN_13


void LED_Init(void)
{
    GPIO_EnableClock(LED_PORT);

    GPIO_Config_t gpio;

    gpio.Mode = GPIO_DRV_MODE_OUTPUT;
    gpio.OutputType = GPIO_OUTPUT_PUSHPULL;
    gpio.Speed = GPIO_DRV_SPEED_HIGH;
    gpio.Pull = GPIO_NO_PULL;
    gpio.AlternateFunction = 0;

    gpio.Pin = RED_PIN;
    GPIO_Init(LED_PORT,&gpio);

    gpio.Pin = GREEN_PIN;
    GPIO_Init(LED_PORT,&gpio);

    gpio.Pin = BLUE_PIN;
    GPIO_Init(LED_PORT,&gpio);
}


void BUTTON_Init(void)
{
    GPIO_EnableClock(BUTTON_PORT);

    GPIO_Config_t gpio;

    gpio.Pin = BUTTON_PIN;
    gpio.Mode = GPIO_DRV_MODE_INPUT;
    gpio.OutputType = GPIO_OUTPUT_PUSHPULL;
    gpio.Speed = GPIO_DRV_SPEED_LOW;
    gpio.Pull = GPIO_PULL_UP;        // or GPIO_NO_PULL if using external resistor
    gpio.AlternateFunction = 0;

    GPIO_Init(BUTTON_PORT,&gpio);
}


uint8_t BUTTON_IsPressed(void)
{
    return (GPIO_ReadPin(BUTTON_PORT, BUTTON_PIN) == GPIO_DRV_PIN_RESET);
}

void LED_SetColor(LED_Color_t color)
{
    /* Turn OFF all LEDs */

	GPIO_WritePin(LED_PORT, RED_PIN, GPIO_DRV_PIN_RESET);
	GPIO_WritePin(LED_PORT, GREEN_PIN, GPIO_DRV_PIN_RESET);
	GPIO_WritePin(LED_PORT, BLUE_PIN, GPIO_DRV_PIN_RESET);

    switch(color)
    {
        case LED_RED:
            GPIO_WritePin(LED_PORT,RED_PIN,GPIO_DRV_PIN_SET);
            break;

        case LED_GREEN:
            GPIO_WritePin(LED_PORT,GREEN_PIN,GPIO_DRV_PIN_SET);
            break;

        case LED_BLUE:
            GPIO_WritePin(LED_PORT,BLUE_PIN,GPIO_DRV_PIN_SET);
            break;

        case LED_YELLOW:
            GPIO_WritePin(LED_PORT,RED_PIN,GPIO_DRV_PIN_SET);
            GPIO_WritePin(LED_PORT,GREEN_PIN,GPIO_DRV_PIN_SET);
            break;

        case LED_PURPLE:
            GPIO_WritePin(LED_PORT,RED_PIN,GPIO_DRV_PIN_SET);
            GPIO_WritePin(LED_PORT,BLUE_PIN,GPIO_DRV_PIN_SET);
            break;

        case LED_CYAN:
            GPIO_WritePin(LED_PORT,GREEN_PIN,GPIO_DRV_PIN_SET);
            GPIO_WritePin(LED_PORT,BLUE_PIN,GPIO_DRV_PIN_SET);
            break;

        case LED_WHITE:
            GPIO_WritePin(LED_PORT,RED_PIN,GPIO_DRV_PIN_SET);
            GPIO_WritePin(LED_PORT,GREEN_PIN,GPIO_DRV_PIN_SET);
            GPIO_WritePin(LED_PORT,BLUE_PIN,GPIO_DRV_PIN_SET);
            break;

        default:
            break;
    }
}

void LED_Update(ECU_Fault_t fault)
{
    uint8_t faultCount = 0;

    if(fault.overTemperature) faultCount++;
    if(fault.lowFuel)         faultCount++;
    if(fault.overSpeed)       faultCount++;
    if(fault.overRPM)         faultCount++;

    if(faultCount == 0)
    {
        LED_SetColor(LED_GREEN);
    }
    else if(faultCount == 1)
    {
        LED_SetColor(LED_RED);
    }
    else if(faultCount == 2)
    {
        LED_SetColor(LED_YELLOW);
    }
    else
    {
        LED_SetColor(LED_PURPLE);
    }
}

#include "ecu.h"

