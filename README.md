# The Ticker
This project is an application that allows data to be transmitted via UART and displayed on a 4-digit 8x8 LED matrix using the MAX7219 microchip. The project is based on the FreeRTOS operating system and is divided into several modules:
* Heartbeat (controls the status LED, which helps determine whether the program is running or not);
* LedMatrix (takes a pointer to a string and converts it into data for display on the LED matrix);
* UART (receives data through USART, extracts the string from the receive buffer, and passes a pointer to it to the LedMatrix module);

This project was created to acquire practical skills in working with UART, SPI, DMA, as well as developing custom drivers for STM32 peripherals. With the exception of the RCC module, which is configured using SPL libraries, all drivers were written from scratch.

An example of the device is located below

<p align = "center">
	<img src="https://github.com/UladShumeika/TheTicker/blob/main/Third%20party%20files/TheTickerExample.gif" alt="Device operation example">
</p>
