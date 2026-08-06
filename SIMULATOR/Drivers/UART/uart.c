/*
 * uart.c
 *
 *  Created on: Jul 20, 2026
 *      Author: Veda Varshita A
 */
//
//#include "uart.h"
//#include "uart_private.h"
//#include "gpio.h"
//#include "stm32f4xx.h"
//
//UART_Status_t UART_Init(void)
//{
//
//    /*---------------------------------------------------------
//     * Step 1 : Enable USART2 Clock
//     *--------------------------------------------------------*/
//    RCC->APB1ENR |= UART_USART2_CLK_EN;
//
//    /* Enable GPIOA Clock */
//    GPIO_EnableClock(GPIO_PORT_A);
//
//    /*------------------- PA2 : USART2_TX -------------------*/
//    GPIO_Config_t uartTx;
//
//    uartTx.Pin = GPIO_DRV_PIN_2;
//    uartTx.Mode = GPIO_DRV_MODE_AF;
//    uartTx.OutputType = GPIO_OUTPUT_PUSHPULL;
//    uartTx.Speed = GPIO_DRV_SPEED_VERY_HIGH;
//    uartTx.Pull = GPIO_NO_PULL;
//    uartTx.AlternateFunction = GPIO_AF7_USART2;
//
//    GPIO_Init(GPIO_PORT_A, &uartTx);
//
//    /*------------------- PA3 : USART2_RX -------------------*/
//    GPIO_Config_t uartRx;
//
//    uartRx.Pin = GPIO_DRV_PIN_3;
//    uartRx.Mode = GPIO_DRV_MODE_AF;
//    uartRx.OutputType = GPIO_OUTPUT_PUSHPULL;
//    uartRx.Speed = GPIO_DRV_SPEED_VERY_HIGH;
//    uartRx.Pull = GPIO_NO_PULL;
//    uartRx.AlternateFunction = GPIO_AF7_USART2;
//
//    GPIO_Init(GPIO_PORT_A, &uartRx);
//
//    /* Configure Baud Rate (42 MHz -> 115200 baud) */
//    USART2->BRR = (22U << 4) | (13U);
////    uint32_t usartdiv;
////    uint32_t mantissa;
////    uint32_t fraction;
////
////    usartdiv = 42000000U / (16U * UART_DEFAULT_BAUDRATE);
////
////    mantissa = usartdiv;
////
////    fraction = (((42000000U * 25U) / (4U * UART_DEFAULT_BAUDRATE)) % 100U * 16U) / 100U;
////
////    USART2->BRR = (mantissa << 4) | (fraction & 0x0FU);
//
//    /* Force parity OFF */
////    USART2->CR1 &= ~UART_CR1_PCE;
////    USART2->CR1 &= ~UART_CR1_PS;
//
//    /* Clear parity configuration */
//    USART2->CR1 &= ~(UART_CR1_PCE | UART_CR1_PS);
//
//#if (UART_DEFAULT_PARITY == UART_PARITY_EVEN)
//
//    USART2->CR1 |= UART_CR1_PCE;
//
//#elif (UART_DEFAULT_PARITY == UART_PARITY_ODD)
//
//    USART2->CR1 |= UART_CR1_PCE;
//
//    USART2->CR1 |= UART_CR1_PS;
//
//#endif
//
//    /* Select 8-bit word length */
//    USART2->CR1 &= ~UART_CR1_M;
//
//    /*  Enable Transmitter (TX) */
//
//    USART2->CR1 |= UART_CR1_TE;
//
//    /* Enable Receiver (RX) */
//
//    USART2->CR1 |= UART_CR1_RE;
//
//    /* Enable USART */
//
//    USART2->CR1 |= UART_CR1_UE;
//
//    return UART_OK;
//}
//
//UART_Status_t UART_SendChar(uint8_t data)
//{
//    while (!(USART2->SR & UART_SR_TXE));
//
//    USART2->DR = data;
//
//    return UART_OK;
//}
//
//UART_Status_t UART_SendString(const char *str)
//{
//    while (*str)
//    {
//        UART_SendChar(*str);
//        str++;
//    }
//
//    return UART_OK;
//}
//
//uint8_t UART_ReadChar(void)
//{
//    while (!(USART2->SR & UART_SR_RXNE));
//
//    return USART2->DR;
//}
//
//uint8_t UART_DataAvailable(void)
//{
//    if (USART2->SR & UART_SR_RXNE)
//    {
//        return 1U;
//    }
//
//    return 0U;
//}
//
//UART_Status_t UART_ReadString(char *buffer, uint16_t maxLength)
//{
//    uint16_t i = 0;
//    char ch;
//
//    while (i < (maxLength - 1))
//    {
//        ch = UART_ReadChar();
//
//        /* Echo the received character */
//        UART_SendChar(ch);
//
//        /* ';' marks the end of the command */
//        if (ch == ';')
//        {
//            break;
//        }
//
//        buffer[i++] = ch;
//    }
//
//    /* Null terminate the string */
//    buffer[i] = '\0';
//
//    return UART_OK;
//}


#include "uart.h"
#include "uart_private.h"
#include "gpio.h"
#include "stm32f4xx.h"

static USART_TypeDef *UART_GetInstance(UART_Instance_t instance)
{
    if(instance == UART1)
        return USART1;

    return USART2;
}

UART_Status_t UART_Init(UART_Instance_t instance)
{
    USART_TypeDef *UARTx = UART_GetInstance(instance);

    GPIO_EnableClock(GPIO_PORT_A);

    if(instance == UART1)
    {
        RCC->APB2ENR |= UART_USART1_CLK_EN;

        GPIO_Config_t tx =
        {
            GPIO_DRV_PIN_9,
            GPIO_DRV_MODE_AF,
            GPIO_OUTPUT_PUSHPULL,
            GPIO_DRV_SPEED_VERY_HIGH,
            GPIO_NO_PULL,
            GPIO_AF7_USART1
        };

        GPIO_Config_t rx =
        {
            GPIO_DRV_PIN_10,
            GPIO_DRV_MODE_AF,
            GPIO_OUTPUT_PUSHPULL,
            GPIO_DRV_SPEED_VERY_HIGH,
            GPIO_NO_PULL,
            GPIO_AF7_USART1
        };

        GPIO_Init(GPIO_PORT_A,&tx);
        GPIO_Init(GPIO_PORT_A,&rx);

        /* 84 MHz APB2 */
        UARTx->BRR = (45U<<4)|(9U);
    }
    else
    {
        RCC->APB1ENR |= UART_USART2_CLK_EN;

        GPIO_Config_t tx =
        {
            GPIO_DRV_PIN_2,
            GPIO_DRV_MODE_AF,
            GPIO_OUTPUT_PUSHPULL,
            GPIO_DRV_SPEED_VERY_HIGH,
            GPIO_NO_PULL,
            GPIO_AF7_USART2
        };

        GPIO_Config_t rx =
        {
            GPIO_DRV_PIN_3,
            GPIO_DRV_MODE_AF,
            GPIO_OUTPUT_PUSHPULL,
            GPIO_DRV_SPEED_VERY_HIGH,
            GPIO_NO_PULL,
            GPIO_AF7_USART2
        };

        GPIO_Init(GPIO_PORT_A,&tx);
        GPIO_Init(GPIO_PORT_A,&rx);

        /* 42 MHz APB1 */
        UARTx->BRR = (22U<<4)|(13U);
    }

    UARTx->CR1 &= ~(UART_CR1_PCE | UART_CR1_PS);

    UARTx->CR1 &= ~UART_CR1_M;

    UARTx->CR1 |= UART_CR1_TE;

    UARTx->CR1 |= UART_CR1_RE;

    UARTx->CR1 |= UART_CR1_UE;

    return UART_OK;
}

UART_Status_t UART_SendChar(UART_Instance_t instance,uint8_t data)
{
    USART_TypeDef *UARTx = UART_GetInstance(instance);

    while(!(UARTx->SR & UART_SR_TXE));

    UARTx->DR = data;

    return UART_OK;
}

UART_Status_t UART_SendString(UART_Instance_t instance,const char *str)
{
    while(*str)
    {
        UART_SendChar(instance,*str++);
    }

    return UART_OK;
}

uint8_t UART_ReadChar(UART_Instance_t instance)
{
    USART_TypeDef *UARTx = UART_GetInstance(instance);

    while(!(UARTx->SR & UART_SR_RXNE));

    return UARTx->DR;
}

uint8_t UART_DataAvailable(UART_Instance_t instance)
{
    USART_TypeDef *UARTx = UART_GetInstance(instance);

    if(UARTx->SR & UART_SR_RXNE)
        return 1;

    return 0;
}

UART_Status_t UART_ReadString(UART_Instance_t instance, char *buffer, uint16_t maxLength)
{
    uint16_t i=0;

    char ch;

    while(i<(maxLength-1))
    {
        ch=UART_ReadChar(instance);

        UART_SendChar(instance,ch);

        if(ch==';')
            break;

        buffer[i++]=ch;
    }

    buffer[i]='\0';

    return UART_OK;
}
