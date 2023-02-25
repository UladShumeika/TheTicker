//---------------------------------------------------------------------------
// Define to prevent recursive inclusion
//---------------------------------------------------------------------------
#ifndef __UART_H
#define __UART_H

//---------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------
#include "main.h"
#include "ush_stm32f4xx_uart.h"

//---------------------------------------------------------------------------
// Typedefs and enumerations
//---------------------------------------------------------------------------

/**
 * @brief UART message structure
 */
typedef struct
{
	uint8_t *message;		/* The pointer to received message */
	uint8_t sizeMessage;	/* The size of received message */
} UART_messageTypeDef;

//---------------------------------------------------------------------------
// External function prototypes
//---------------------------------------------------------------------------
void UART_freeRtosInit(void);
void receivingMessageTask(void const *argument);

#endif /* __UART_H */
