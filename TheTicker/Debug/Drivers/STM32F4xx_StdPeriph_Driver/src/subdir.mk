################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/STM32F4xx_StdPeriph_Driver/src/misc.c \
../Drivers/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dma.c \
../Drivers/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_flash.c \
../Drivers/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_gpio.c \
../Drivers/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rcc.c \
../Drivers/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_spi.c \
../Drivers/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_usart.c 

OBJS += \
./Drivers/STM32F4xx_StdPeriph_Driver/src/misc.o \
./Drivers/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dma.o \
./Drivers/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_flash.o \
./Drivers/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_gpio.o \
./Drivers/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rcc.o \
./Drivers/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_spi.o \
./Drivers/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_usart.o 

C_DEPS += \
./Drivers/STM32F4xx_StdPeriph_Driver/src/misc.d \
./Drivers/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dma.d \
./Drivers/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_flash.d \
./Drivers/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_gpio.d \
./Drivers/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rcc.d \
./Drivers/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_spi.d \
./Drivers/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_usart.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/STM32F4xx_StdPeriph_Driver/src/%.o Drivers/STM32F4xx_StdPeriph_Driver/src/%.su: ../Drivers/STM32F4xx_StdPeriph_Driver/src/%.c Drivers/STM32F4xx_StdPeriph_Driver/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F4xx_StdPeriph_Driver/inc -I../Drivers/CMSIS/STM32F4xx/ -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"c:/st/stm32cubeide_1.9.0/stm32cubeide/plugins/com.st.stm32cube.ide.mcu.externaltools.gnu-tools-for-stm32.10.3-2021.10.win32_1.0.0.202111181127/tools/arm-none-eabi/include/" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-STM32F4xx_StdPeriph_Driver-2f-src

clean-Drivers-2f-STM32F4xx_StdPeriph_Driver-2f-src:
	-$(RM) ./Drivers/STM32F4xx_StdPeriph_Driver/src/misc.d ./Drivers/STM32F4xx_StdPeriph_Driver/src/misc.o ./Drivers/STM32F4xx_StdPeriph_Driver/src/misc.su ./Drivers/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dma.d ./Drivers/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dma.o ./Drivers/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dma.su ./Drivers/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_flash.d ./Drivers/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_flash.o ./Drivers/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_flash.su ./Drivers/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_gpio.d ./Drivers/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_gpio.o ./Drivers/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_gpio.su ./Drivers/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rcc.d ./Drivers/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rcc.o ./Drivers/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rcc.su ./Drivers/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_spi.d ./Drivers/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_spi.o ./Drivers/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_spi.su ./Drivers/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_usart.d ./Drivers/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_usart.o ./Drivers/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_usart.su

.PHONY: clean-Drivers-2f-STM32F4xx_StdPeriph_Driver-2f-src

