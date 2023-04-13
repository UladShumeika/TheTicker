//---------------------------------------------------------------------------
// Define to prevent recursive inclusion
//---------------------------------------------------------------------------
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

//---------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------
#include "stm32f4xx.h"

#include "cmsis_os.h"

#include <stdio.h>

//---------------------------------------------------------------------------
// Defines
//---------------------------------------------------------------------------
#define HEARTBEAT
#define LEDMATRIX
#define UART

//---------------------------------------------------------------------------
// Module's includes
//---------------------------------------------------------------------------
#ifdef HEARTBEAT
	#include "heartbeat.h"
#endif

#ifdef LEDMATRIX
	#include "LedMatrix.h"
#endif

#ifdef UART
	#include "uart.h"
#endif

//---------------------------------------------------------------------------
// External function prototypes
//---------------------------------------------------------------------------
void freeRtosInit(void);

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
