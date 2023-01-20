//---------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------
#include <ush_spi.h>
#include "MAX7219.h"

//---------------------------------------------------------------------------
// Library Functions
//---------------------------------------------------------------------------


void MAX7219_init(void)
{
	USH_SPI_initDefaultTypeDef initStructure = {0,};

	initStructure.SPIx = SPI1;
	initStructure.PinsPack = SPI_PINSPACK_1;
	initStructure.BaudRatePrescaler = SPI_BAUDRATE_PRESCALER_16;
	initStructure.Mode = SPI_MODE_1;
	SPI_init(&initStructure);
}
