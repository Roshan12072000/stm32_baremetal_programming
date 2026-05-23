################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/src/STM32_Spi_Driver.c \
../drivers/src/stm32l476xx_gpio_driver.c \
../drivers/src/stm32l476xx_i2c_driver.c \
../drivers/src/stm32l476xx_uart_driver.c 

OBJS += \
./drivers/src/STM32_Spi_Driver.o \
./drivers/src/stm32l476xx_gpio_driver.o \
./drivers/src/stm32l476xx_i2c_driver.o \
./drivers/src/stm32l476xx_uart_driver.o 

C_DEPS += \
./drivers/src/STM32_Spi_Driver.d \
./drivers/src/stm32l476xx_gpio_driver.d \
./drivers/src/stm32l476xx_i2c_driver.d \
./drivers/src/stm32l476xx_uart_driver.d 


# Each subdirectory must supply rules for building sources it contributes
drivers/src/%.o drivers/src/%.su drivers/src/%.cyclo: ../drivers/src/%.c drivers/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32L4 -DSTM32 -DNUCLEO_L476RG -DSTM32L476RGTx -c -I../Inc -I"D:/Stm_baremetal_workspace/UART_Interrupt_Driver/drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-drivers-2f-src

clean-drivers-2f-src:
	-$(RM) ./drivers/src/STM32_Spi_Driver.cyclo ./drivers/src/STM32_Spi_Driver.d ./drivers/src/STM32_Spi_Driver.o ./drivers/src/STM32_Spi_Driver.su ./drivers/src/stm32l476xx_gpio_driver.cyclo ./drivers/src/stm32l476xx_gpio_driver.d ./drivers/src/stm32l476xx_gpio_driver.o ./drivers/src/stm32l476xx_gpio_driver.su ./drivers/src/stm32l476xx_i2c_driver.cyclo ./drivers/src/stm32l476xx_i2c_driver.d ./drivers/src/stm32l476xx_i2c_driver.o ./drivers/src/stm32l476xx_i2c_driver.su ./drivers/src/stm32l476xx_uart_driver.cyclo ./drivers/src/stm32l476xx_uart_driver.d ./drivers/src/stm32l476xx_uart_driver.o ./drivers/src/stm32l476xx_uart_driver.su

.PHONY: clean-drivers-2f-src

