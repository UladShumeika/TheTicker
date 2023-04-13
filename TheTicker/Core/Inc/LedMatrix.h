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
// External function prototypes
//---------------------------------------------------------------------------
void LEDMATRIX_freeRtosInit(void);
void sendToTheMatrixTask(void const *argument);
void convertStringIntoDataForMatrixTask(void const *argument);

#endif /* __LEDMATRIX_H */
