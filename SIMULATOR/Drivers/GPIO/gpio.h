/*
 * gpio.h
 *
 *  Created on: Jul 21, 2026
 */
#ifndef GPIO_GPIO_H_
#define GPIO_GPIO_H_

#include <stdint.h>
#include "gpio_types.h"
#include "gpio_cfg.h"

typedef struct
{
	GPIO_Pin_t Pin;
	GPIO_Mode_t Mode;
	GPIO_OutputType_t OutputType;
	GPIO_Speed_t Speed;
	GPIO_Pull_t Pull;
	uint8_t AlternateFunction; //AF0 - AF15
}GPIO_Config_t;

void GPIO_EnableClock(GPIO_Port_t port);
void GPIO_Init(GPIO_Port_t port, const GPIO_Config_t *config);
void GPIO_WritePin(GPIO_Port_t port, GPIO_Pin_t pin, GPIO_PinState_t state);
GPIO_PinState_t GPIO_ReadPin(GPIO_Port_t port, GPIO_Pin_t pin);
void GPIO_TogglePin(GPIO_Port_t port, GPIO_Pin_t pin);

#endif /* GPIO_GPIO_H_ */
