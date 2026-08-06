/*
 * gpio.c
 *
 *  Created on: Jul 21, 2026
 */
#include "gpio.h"
#include "gpio_private.h"
#include <stddef.h>

static GPIO_TypeDef *const GPIO_PortBase[GPIO_NUMBER_OF_PORTS] =
{
		GPIOA,
		GPIOB,
		GPIOC,
		GPIOD,
		GPIOH
};

void GPIO_EnableClock(GPIO_Port_t port)
{
    static const uint8_t GPIO_ClockBit[] =
    {
        0U,
        1U,
        2U,
        3U,
        7U
    };

    if(port >= GPIO_NUMBER_OF_PORTS)
    {
        return;
    }

    RCC->AHB1ENR |= (1U << GPIO_ClockBit[port]);
}

void GPIO_Init(GPIO_Port_t port, const GPIO_Config_t *config)
{
    /* Check for invalid port */
    if(port >= GPIO_NUMBER_OF_PORTS)
    {
        return;
    }

    /* Check for NULL Pointer*/
	if(config == NULL)
	{
	    return;
	}

	if(config->Pin >= GPIO_NUMBER_OF_PINS)
	{
	    return;
	}

	GPIO_TypeDef *GPIOx = GPIO_PortBase[port];
	uint32_t position = (uint32_t)(config->Pin * GPIO_MODE_BITS);

    /* Clear the mode bits */
    GPIOx->MODER &= ~(GPIO_2BIT_MASK << position);
    /* Set the new mode */
    GPIOx->MODER |= ((uint32_t)config->Mode << position);

    /* Configure Output Type */
    GPIOx->OTYPER &= ~(GPIO_1BIT_MASK << config->Pin);
    GPIOx->OTYPER |= ((uint32_t)config->OutputType << config->Pin);

    /* Configure Output Speed */
    GPIOx->OSPEEDR &= ~(GPIO_2BIT_MASK << position);
    GPIOx->OSPEEDR |= ((uint32_t)config->Speed << position);

    /* Configure Pull-up/Pull-down */
    GPIOx->PUPDR &= ~(GPIO_2BIT_MASK << position);
    GPIOx->PUPDR |= ((uint32_t)config->Pull << position);

    /* Configure Alternate Function */
    if ((config->Mode == GPIO_DRV_MODE_AF) &&
        (config->AlternateFunction > 15U))
    {
        return;
    }

    if(config->Mode == GPIO_DRV_MODE_AF)
    {
    	uint32_t afrIndex = config->Pin / 8U;
    	uint32_t afPosition = (config->Pin % 8U) * GPIO_AF_BITS;
        GPIOx->AFR[afrIndex] &= ~(GPIO_4BIT_MASK << afPosition);
        GPIOx->AFR[afrIndex] |= ((uint32_t)config->AlternateFunction << afPosition);
    }
}

void GPIO_WritePin(GPIO_Port_t port, GPIO_Pin_t pin, GPIO_PinState_t state)
{
    /* Check for invalid port */
    if(port >= GPIO_NUMBER_OF_PORTS)
    {
        return;
    }

    /* Check for invalid pin */
    if(pin >= GPIO_NUMBER_OF_PINS)
    {
        return;
    }

    GPIO_TypeDef *GPIOx = GPIO_PortBase[port];

    if(state == GPIO_DRV_PIN_SET)
    {
        GPIOx->BSRR = (1U << pin);
    }
    else
    {
        GPIOx->BSRR = (1U << (pin + 16U));
    }
}

GPIO_PinState_t GPIO_ReadPin(GPIO_Port_t port, GPIO_Pin_t pin)
{
    /* Check for invalid port */
    if(port >= GPIO_NUMBER_OF_PORTS)
    {
        return GPIO_DRV_PIN_RESET;
    }

    /* Check for invalid pin */
    if(pin >= GPIO_NUMBER_OF_PINS)
    {
        return GPIO_DRV_PIN_RESET;
    }

    GPIO_TypeDef *GPIOx = GPIO_PortBase[port];

    if(GPIOx->IDR & (1U << pin))
    {
        return GPIO_DRV_PIN_SET;
    }
    else
    {
        return GPIO_DRV_PIN_RESET;
    }
}

void GPIO_TogglePin(GPIO_Port_t port, GPIO_Pin_t pin)
{
    /* Check for invalid port */
    if(port >= GPIO_NUMBER_OF_PORTS)
    {
        return;
    }

    /* Check for invalid pin */
    if(pin >= GPIO_NUMBER_OF_PINS)
    {
        return;
    }

    GPIO_TypeDef *GPIOx = GPIO_PortBase[port];

    GPIOx->ODR ^= (1U << pin);
}

