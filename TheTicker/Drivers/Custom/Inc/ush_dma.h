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

	uint32_t PeriphInc;						/* This parameter specifies whether the peripheral address register should
	                                           be incremented or not. This parameter can be a value of @ref USH_DMA_periphIncrement */

	uint32_t MemInc;						/* This parameter specifies whether the memory address register should
	 	 	 	 	 	 	 	 	 	 	   be incremented or not. This parameter can be a value of @ref USH_DMA_memoryIncrement */

	uint32_t PeriphDataAlignment;			/* This parameter specifies the peripheral data width.
	 	 	 	 	 	 	 	 	 	 	   This parameter can be a value of @ref USH_DMA_periphDataSize */

	uint32_t MemDataAlignment;				/* This parameter specifies the memory data width.
											   This parameter can be a value of @ref USH_DMA_memoryDataSize */

	uint32_t Mode;							/* This parameter specifies the operation mode of the selected stream.
	 	 	 	 	 	 	 	 	 	 	   This parameter can be a value of @ref USH_DMA_mode */

	uint32_t Priority;						/* This parameter specifies the software priority for the selected stream.
	 	 	 	 	 	 	 	 	 	 	   This parameter can be a value of @ref USH_DMA_priority*/

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
	DMA_MEMORY_TO_MEMORY	= 0x80UL		/* Memory to memory direction */
} USH_DMA_dataTransferDirection;

/**
 * @brief DMA peripheral incremented mode enumeration
 */
typedef enum
{
	DMA_PINC_ENABLE		= 0x200UL,		/* Peripheral increment mode enable */
	DMA_PINC_DISABLE	= 0x000UL		/* Peripheral increment mode disable */
} USH_DMA_periphIncrement;

/**
 * @brief DMA memory incremented mode enumeration
 */
typedef enum
{
	DMA_MINC_ENABLE		= 0x400UL,		/* Memory increment mode enable */
	DMA_MINC_DISABLE	= 0x000UL		/* Memory increment mode disable */
} USH_DMA_memoryIncrement;

/**
 * @brief DMA peripheral data size enumeration
 */
typedef enum
{
	DMA_PERIPH_SIZE_BYTE		= 0x000UL,  	/* Peripheral data alignment: Byte */
	DMA_PERIPH_SIZE_HALFWORD	= 0x800UL,		/* Peripheral data alignment: Half word	*/
	DMA_PERIPH_SIZE_WORD		= 0x1000UL		/* Peripheral data alignment: Word */
} USH_DMA_periphDataSize;

/**
 * @brief DMA memory data size enumeration
 */
typedef enum
{
	DMA_MEMORY_SIZE_BYTE		= 0x0000UL,		/* Memory data alignment: Byte */
	DMA_MEMORY_SIZE_HALFWORD	= 0x2000UL,		/* Memory data alignment: Half word */
	DMA_MEMORY_SIZE_WORD		= 0x4000UL		/* Memory data alignment: Word	*/
} USH_DMA_memoryDataSize;

/**
 * @brief DMA mode enumeration
 */
typedef enum
{
	DMA_NORMAL_MODE			= 0x000UL,		/* Normal mode */
	DMA_CIRCULAR_MODE		= 0x100UL,		/* Circular mode */
	DMA_PERIPH_CTRL_MODE	= 0x20UL		/* Peripheral control mode */
} USH_DMA_mode;

/**
 * @brief DMA priority enumeration
 */
typedef enum
{
	DMA_PRIORITY_LOW		= 0x0000UL,		/* Priority level: Low */
	DMA_PRIORITY_MEDIUM		= 0x4000UL,		/* Priority level: Medium */
	DMA_PRIORITY_HIGH		= 0x8000UL,		/* Priority level: High */
	DMA_PRIORITY_VERY_HIGH	= 0x30000UL		/* Priority level: Low */
} USH_DMA_priority;

#endif /* __USH_DMA_H */
