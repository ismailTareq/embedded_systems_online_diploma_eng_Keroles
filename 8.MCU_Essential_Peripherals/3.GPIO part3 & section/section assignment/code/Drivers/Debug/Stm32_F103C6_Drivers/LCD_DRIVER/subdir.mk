################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Stm32_F103C6_Drivers/LCD_DRIVER/LCD.c 

OBJS += \
./Stm32_F103C6_Drivers/LCD_DRIVER/LCD.o 

C_DEPS += \
./Stm32_F103C6_Drivers/LCD_DRIVER/LCD.d 


# Each subdirectory must supply rules for building sources it contributes
Stm32_F103C6_Drivers/LCD_DRIVER/%.o Stm32_F103C6_Drivers/LCD_DRIVER/%.su Stm32_F103C6_Drivers/LCD_DRIVER/%.cyclo: ../Stm32_F103C6_Drivers/LCD_DRIVER/%.c Stm32_F103C6_Drivers/LCD_DRIVER/subdir.mk
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -c -I"C:/Users/ismail/STM32CubeIDE/workspace_1.14.1/Drivers/Stm32_F103C6_Drivers/Inc" -I"C:/Users/ismail/STM32CubeIDE/workspace_1.14.1/Drivers/Stm32_F103C6_Drivers/7_SEG" -I"C:/Users/ismail/STM32CubeIDE/workspace_1.14.1/Drivers/Stm32_F103C6_Drivers/LCD_DRIVER" -I"C:/Users/ismail/STM32CubeIDE/workspace_1.14.1/Drivers/Stm32_F103C6_Drivers/KEYPAD_DRIVER" -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Stm32_F103C6_Drivers-2f-LCD_DRIVER

clean-Stm32_F103C6_Drivers-2f-LCD_DRIVER:
	-$(RM) ./Stm32_F103C6_Drivers/LCD_DRIVER/LCD.cyclo ./Stm32_F103C6_Drivers/LCD_DRIVER/LCD.d ./Stm32_F103C6_Drivers/LCD_DRIVER/LCD.o ./Stm32_F103C6_Drivers/LCD_DRIVER/LCD.su

.PHONY: clean-Stm32_F103C6_Drivers-2f-LCD_DRIVER

