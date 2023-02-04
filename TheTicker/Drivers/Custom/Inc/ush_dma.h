/**
  ******************************************************************************
  * @file    ush_dma.h
  * @author  Ulad Shumeika
  * @version v1.0
  * @date    04-February-2023
  * @brief   Header file of DMA module
  ******************************************************************************
  */

//---------------------------------------------------------------------------
// Define to prevent recursive inclusion
//---------------------------------------------------------------------------
#ifndef __USH_DMA_H
#define __USH_DMA_H

//---------------------------------------------------------------------------
// Typedefs and enumerations
//---------------------------------------------------------------------------

/**
  * @brief DMA initialization structure definition
  */
typedef struct
{
	DMA_Stream_TypeDef* DMAx;				/* A pointer to DMAx peripheral to be used where x is 1 or 2 */

	uint32_t Channel;
	uint32_t Direction;
	uint32_t PeriphInc;
	uint32_t MemInc;
	uint32_t PeriphDataAlignment;
	uint32_t MemDataAlignment;
	uint32_t Mode;
	uint32_t Priority;
	uint32_t FIFOMode;
	uint32_t FIFOThreshold;
	uint32_t PeriphBurst;
} USH_DMA_initTypeDef;



#endif /* __USH_DMA_H */
