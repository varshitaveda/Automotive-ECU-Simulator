/*
 * gpio_private.h
 *
 *  Created on: Jul 21, 2026
 */

#ifndef GPIO_GPIO_PRIVATE_H_
#define GPIO_GPIO_PRIVATE_H_

#include "stm32f411xe.h"

//#define GPIO_NUMBER_OF_PORTS  (5U)
#define GPIO_NUMBER_OF_PINS   (16U)

#define GPIO_MODE_BITS        (2U)
#define GPIO_AF_BITS          (4U)

#define GPIO_1BIT_MASK        (0x01U)
#define GPIO_2BIT_MASK        (0x03U)
#define GPIO_4BIT_MASK        (0x0FU)

#endif /* GPIO_GPIO_PRIVATE_H_ */
