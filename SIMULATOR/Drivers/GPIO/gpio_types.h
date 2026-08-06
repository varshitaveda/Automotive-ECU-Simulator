/*
 * gpio_types.h
 *
 *  Created on: Jul 21, 2026
 */

#ifndef GPIO_GPIO_TYPES_H_
#define GPIO_GPIO_TYPES_H_

#include <stdint.h>

#define GPIO_AF7_USART2    7U

typedef enum
{
	GPIO_PORT_A = 0,
	GPIO_PORT_B,
	GPIO_PORT_C,
	GPIO_PORT_D,
	GPIO_PORT_H,
	GPIO_NUMBER_OF_PORTS
}GPIO_Port_t;

typedef enum
{
    GPIO_DRV_PIN_0 = 0,
    GPIO_DRV_PIN_1,
    GPIO_DRV_PIN_2,
    GPIO_DRV_PIN_3,
    GPIO_DRV_PIN_4,
    GPIO_DRV_PIN_5,
    GPIO_DRV_PIN_6,
    GPIO_DRV_PIN_7,
    GPIO_DRV_PIN_8,
    GPIO_DRV_PIN_9,
    GPIO_DRV_PIN_10,
    GPIO_DRV_PIN_11,
    GPIO_DRV_PIN_12,
    GPIO_DRV_PIN_13,
    GPIO_DRV_PIN_14,
    GPIO_DRV_PIN_15
} GPIO_Pin_t;

typedef enum
{
    GPIO_DRV_MODE_INPUT = 0x00,
    GPIO_DRV_MODE_OUTPUT = 0x01,
    GPIO_DRV_MODE_AF = 0x02,
    GPIO_DRV_MODE_ANALOG = 0x03
} GPIO_Mode_t;

typedef enum
{
    GPIO_OUTPUT_PUSHPULL = 0x00,
    GPIO_OUTPUT_OPENDRAIN = 0x01
} GPIO_OutputType_t;

typedef enum
{
    GPIO_DRV_SPEED_LOW = 0x00,
    GPIO_DRV_SPEED_MEDIUM = 0x01,
    GPIO_DRV_SPEED_HIGH = 0x02,
    GPIO_DRV_SPEED_VERY_HIGH = 0x03
} GPIO_Speed_t;

typedef enum
{
    GPIO_NO_PULL = 0x00,
    GPIO_PULL_UP = 0x01,
    GPIO_PULL_DOWN = 0x02
} GPIO_Pull_t;

typedef enum
{
    GPIO_DRV_PIN_RESET = 0,
    GPIO_DRV_PIN_SET = 1
} GPIO_PinState_t;


#endif /* GPIO_GPIO_TYPES_H_ */
