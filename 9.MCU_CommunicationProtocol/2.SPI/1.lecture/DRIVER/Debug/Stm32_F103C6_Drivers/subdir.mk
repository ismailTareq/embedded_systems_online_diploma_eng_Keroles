################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Stm32_F103C6_Drivers/EXTI.c \
../Stm32_F103C6_Drivers/GPIO.c \
../Stm32_F103C6_Drivers/RCC.c \
../Stm32_F103C6_Drivers/SPI.c \
../Stm32_F103C6_Drivers/USART.c 

OBJS += \
./Stm32_F103C6_Drivers/EXTI.o \
./Stm32_F103C6_Drivers/GPIO.o \
./Stm32_F103C6_Drivers/RCC.o \
./Stm32_F103C6_Drivers/SPI.o \
./Stm32_F103C6_Drivers/USART.o 

C_DEPS += \
./Stm32_F103C6_Drivers/EXTI.d \
./Stm32_F103C6_Drivers/GPIO.d \
./Stm32_F103C6_Drivers/RCC.d \
./Stm32_F103C6_Drivers/SPI.d \
./Stm32_F103C6_Drivers/USART.d 


# Each subdirectory must supply rules for building sources it contributes
Stm32_F103C6_Drivers/%.o Stm32_F103C6_Drivers/%.su Stm32_F103C6_Drivers/%.cyclo: ../Stm32_F103C6_Drivers/%.c Stm32_F103C6_Drivers/subdir.mk
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -c -I"C:/Users/ismail/STM32CubeIDE/Drivers/HAL/Inc" -I"C:/Users/ismail/STM32CubeIDE/Drivers/Stm32_F103C6_Drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Stm32_F103C6_Drivers

clean-Stm32_F103C6_Drivers:
	-$(RM) ./Stm32_F103C6_Drivers/EXTI.cyclo ./Stm32_F103C6_Drivers/EXTI.d ./Stm32_F103C6_Drivers/EXTI.o ./Stm32_F103C6_Drivers/EXTI.su ./Stm32_F103C6_Drivers/GPIO.cyclo ./Stm32_F103C6_Drivers/GPIO.d ./Stm32_F103C6_Drivers/GPIO.o ./Stm32_F103C6_Drivers/GPIO.su ./Stm32_F103C6_Drivers/RCC.cyclo ./Stm32_F103C6_Drivers/RCC.d ./Stm32_F103C6_Drivers/RCC.o ./Stm32_F103C6_Drivers/RCC.su ./Stm32_F103C6_Drivers/SPI.cyclo ./Stm32_F103C6_Drivers/SPI.d ./Stm32_F103C6_Drivers/SPI.o ./Stm32_F103C6_Drivers/SPI.su ./Stm32_F103C6_Drivers/USART.cyclo ./Stm32_F103C6_Drivers/USART.d ./Stm32_F103C6_Drivers/USART.o ./Stm32_F103C6_Drivers/USART.su

.PHONY: clean-Stm32_F103C6_Drivers

