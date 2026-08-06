/*
 * uart_types.h
 *
 *  Created on: Jul 20, 2026
 *      Author: Veda Varshita A
 */

#ifndef UART_UART_TYPES_H_
#define UART_UART_TYPES_H_
#include <stdint.h>

/*=========================================
 * UART Driver Status
 *=========================================*/
typedef enum
{
    UART_OK = 0,
    UART_ERROR

} UART_Status_t;

/*=========================================
 * UART instance type
 *=========================================*/

typedef enum
{
    UART1 = 0,
    UART2

}UART_Instance_t;
/*=========================================
 * UART Baud Rates
 *=========================================*/
typedef enum
{
    UART_BAUDRATE_9600   = 9600,
    UART_BAUDRATE_19200  = 19200,
    UART_BAUDRATE_38400  = 38400,
    UART_BAUDRATE_57600  = 57600,
    UART_BAUDRATE_115200 = 115200

} UART_BaudRate_t;


/*=========================================
 * PARITY SELECT
 *=========================================*/

#define UART_PARITY_NONE  0U
#define UART_PARITY_EVEN  1U
#define UART_PARITY_ODD   2U

#endif /* UART_UART_TYPES_H_ */
