/**
  ******************************************************************************
  * @file    ush_dma.c
  * @author  Ulad Shumeika
  * @version v1.0
  * @date    05-February-2023
  * @brief   DMA module driver
  ******************************************************************************
  */

//---------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------
#include "ush_dma.h"

//---------------------------------------------------------------------------
// Initialization functions
//---------------------------------------------------------------------------

/**
 * @brief 	This function initializes the DMAx peripheral according to the specified parameters in the USH_DMA_initTypeDef.
 * @param 	initStructure - A pointer to a USH_DMA_initTypeDef structure that contains the configuration
 * 							information for the specified DMA peripheral.
 * @retval	None.
 */
void DMA_init(USH_DMA_initTypeDef *initStructure)
{
	uint32_t temp = 0;


}

//---------------------------------------------------------------------------
// Library Functions
//---------------------------------------------------------------------------

/**
 * @brief 	This function enables and disables the selected DMA stream.
 * @param 	DMAx_Streamy - A pointer to a DMA_Stream_TypeDef structure that contains the selected DMA stream.
 * @param 	state - The state of the selected stream. This parameter can be a value of @ref FunctionalState.
 * @retval	None.
 */
void DMA_state(DMA_Stream_TypeDef *DMAx_Streamy, FunctionalState state)
{
	if(state == ENABLE)
	{
		DMAx_Streamy->CR |= DMA_SxCR_EN;
	} else
	{
		DMAx_Streamy->CR &= ~DMA_SxCR_EN;
	}
}
