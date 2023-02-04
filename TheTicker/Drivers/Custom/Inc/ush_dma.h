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


	uint32_t Channel;						/* A channel to be used for the specified stream.
											   This parameter can be a value of @ref USH_DMA_channels */

	uint32_t Direction;						/* A direction to be used for the specified stream.
											   This parameter can be a value of @ref USH_DMA_dataTransferDirection */

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

/**
 * @brief DMA channels enumeration to select the channel for DMA
 */
typedef enum
{
	DMA_CHANNEL_0	= 0x00000000U,		/* DMA Channel 0 */
	DMA_CHANNEL_1	= 0x02000000U,		/* DMA Channel 1 */
	DMA_CHANNEL_2	= 0x04000000U,		/* DMA Channel 2 */
	DMA_CHANNEL_3	= 0x06000000U,		/* DMA Channel 3 */
	DMA_CHANNEL_4 	= 0x08000000U,		/* DMA Channel 4 */
	DMA_CHANNEL_5	= 0x0A000000U,		/* DMA Channel 5 */
	DMA_CHANNEL_6	= 0x0C000000U,		/* DMA Channel 6 */
	DMA_CHANNEL_7	= 0x0E000000U		/* DMA Channel 7 */
} USH_DMA_channels;

/**
 * @brief DMA data transfer direction enumeration
 */
typedef enum
{
	DMA_PERIPH_TO_MEMORY	= 0x00UL,		/* Peripheral to memory direction */
	DMA_MEMORY_TO_PERIPH	= 0x40UL,		/* Memory to peripheral direction */
	DMA_MEMORY_TO_MEMORY	= 0x80UL		/* Memory to memory direction	  */
} USH_DMA_dataTransferDirection;

#endif /* __USH_DMA_H */
