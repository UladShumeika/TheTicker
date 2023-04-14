/**
  ******************************************************************************
  * @file    ush_stm32f4xx_dma.h
  * @author  Ulad Shumeika
  * @version v1.0
  * @date    04-February-2023
  * @brief   Header file of DMA module
  *
  ******************************************************************************
  */

//---------------------------------------------------------------------------
// Define to prevent recursive inclusion
//---------------------------------------------------------------------------
#ifndef __USH_STM32F4XX_DMA_H
#define __USH_STM32F4XX_DMA_H

//---------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------
#include "stm32f4xx.h"

//---------------------------------------------------------------------------
// Typedefs and enumerations
//---------------------------------------------------------------------------

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

#endif /* __USH_STM32F4XX_DMA_H */
