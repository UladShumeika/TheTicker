//---------------------------------------------------------------------------
// Define to prevent recursive inclusion
//---------------------------------------------------------------------------
#ifndef __UART_H
#define __UART_H

//---------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------
#include "main.h"

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
void idleIRQTask(void const *argument);
uint8_t* getPointerDefaultString(void);

#endif /* __UART_H */
