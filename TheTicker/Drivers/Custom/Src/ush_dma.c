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
#include "stm32f4xx.h"

//---------------------------------------------------------------------------
// Static function prototypes
//---------------------------------------------------------------------------
static uint32_t DMA_calcBaseAndIndex(USH_DMA_initTypeDef *initStructure);

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

	DMA_state(initStructure->Stream, DISABLE);

	// Get the CR register value
	temp = initStructure->Stream->CR;


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

/**
 * @brief 	This function returns the DMA stream base address depending on stream number.
 * @param 	initStructure - A pointer to a USH_DMA_initTypeDef structure that contains the configuration
 * 							information for the specified DMA peripheral.
 * @return	Stream base address.
 */
static uint32_t DMA_calcBaseAndIndex(USH_DMA_initTypeDef *initStructure)
{
	uint32_t streamNumber = (((uint32_t)initStructure->Stream & 0xFFU) - 16U) / 24U;

	// lookup table for necessary stream index of flags within status registers
	static const uint8_t flagBitshiftOffset[8U] = {0U, 6U, 16U, 22U, 0U, 6U, 16U, 22U};
	initStructure->StreamIndex = flagBitshiftOffset[streamNumber];

	if (streamNumber > 3U)
	{
		// return pointer to HISR and HIFCR
		initStructure->StreamBaseAddress = (((uint32_t)initStructure->Stream & (uint32_t)(~0x3FFU)) + 4U);
	} else
	{
	    // return pointer to LISR and LIFCR
		initStructure->StreamBaseAddress = ((uint32_t)initStructure->Stream & (uint32_t)(~0x3FFU));
	}

	return initStructure->StreamBaseAddress;
}
