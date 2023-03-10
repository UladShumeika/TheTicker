//---------------------------------------------------------------------------
// Define to prevent recursive inclusion
//---------------------------------------------------------------------------
#ifndef __LEDMATRIX_H
#define __LEDMATRIX_H

//---------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------
#include "main.h"
#include "MAX7219.h"

//---------------------------------------------------------------------------
// Defines
//---------------------------------------------------------------------------
#define OUTPUT_BUFFER_MIN_ROW		MATRIX_DIGITS
#define OUTPUT_BUFFER_COLUMN		MATRIX_HIGH

//---------------------------------------------------------------------------
// External function prototypes
//---------------------------------------------------------------------------
void LEDMATRIX_freeRtosInit(void);
void sendToTheMatrixTask(void const *argument);
void convertStringIntoDataForMatrixTask(void const *argument);

#endif /* __LEDMATRIX_H */
