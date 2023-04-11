//---------------------------------------------------------------------------
// Define to prevent recursive inclusion
//---------------------------------------------------------------------------
#ifndef __HEARTBEAT_H
#define __HEARTBEAT_H

//---------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------
#include "main.h"

//---------------------------------------------------------------------------
// External function prototypes
//---------------------------------------------------------------------------
void HeartbeatTask(void const * argument);
void HEARTBEAT_freeRtosInit(void);

#endif /* __HEARTBEAT_H */
