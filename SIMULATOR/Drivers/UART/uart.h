/*
 * uart.h
 *
 *  Created on: Jul 20, 2026
 *      Author: Veda Varshita A
 */

#ifndef UART_UART_H_
#define UART_UART_H_

#include <stdint.h>

#include "uart_types.h"
#include "uart_cfg.h"

/*=========================================
 * Public API
 *=========================================*/

//UART_Status_t UART_Init(UART_Instance_t instance);
//
//UART_Status_t UART_SendChar(uint8_t data);
//
//UART_Status_t UART_SendString(const char *str);
//
//uint8_t UART_ReadChar(void);
//
//UART_Status_t UART_ReadString(char *buffer, uint16_t maxLength);
//
//uint8_t UART_DataAvailable(void);

UART_Status_t UART_Init(UART_Instance_t instance);

UART_Status_t UART_SendChar(UART_Instance_t instance,uint8_t data);

UART_Status_t UART_SendString(UART_Instance_t instance,const char *str);

uint8_t UART_ReadChar(UART_Instance_t instance);

uint8_t UART_DataAvailable(UART_Instance_t instance);

UART_Status_t UART_ReadString(UART_Instance_t instance, char *buffer, uint16_t maxLength);

#endif /* UART_UART_H_ */
