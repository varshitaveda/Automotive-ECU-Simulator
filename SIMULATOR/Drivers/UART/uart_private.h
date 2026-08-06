/*
 * uart_private.h
 *
 *  Created on: Jul 20, 2026
 *      Author: Veda Varshita A
 */

#ifndef UART_UART_PRIVATE_H_
#define UART_UART_PRIVATE_H_

/*=========================================
 * RCC Clock Enable Bits
 *=========================================*/

#define UART_GPIOA_CLK_EN      (1U << 0)
#define UART_USART2_CLK_EN     (1U << 17)
#define UART_USART1_CLK_EN     (1U <<  4)
/*=========================================
 * USART Control Register 1 (CR1)
 *=========================================*/

#define UART_CR1_RE            (1U << 2)
#define UART_CR1_TE            (1U << 3)
#define UART_CR1_UE            (1U << 13)
#define UART_CR1_PS      	   (1U << 9)
#define UART_CR1_PCE           (1U << 10)
#define UART_CR1_M             (1U << 12)
/*=========================================
 * USART Status Register (SR)
 *=========================================*/

#define UART_SR_RXNE           (1U << 5)
#define UART_SR_TXE            (1U << 7)


#endif /* UART_UART_PRIVATE_H_ */
