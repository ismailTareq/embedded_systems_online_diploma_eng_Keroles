################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Stm32_F103C6_Drivers/EXTI.c \
../Stm32_F103C6_Drivers/GPIO.c 

OBJS += \
./Stm32_F103C6_Drivers/EXTI.o \
./Stm32_F103C6_Drivers/GPIO.o 

C_DEPS += \
./Stm32_F103C6_Drivers/EXTI.d \
./Stm32_F103C6_Drivers/GPIO.d 


# Each subdirectory must supply rules for building sources it contributes
Stm32_F103C6_Drivers/%.o Stm32_F103C6_Drivers/%.su Stm32_F103C6_Drivers/%.cyclo: ../Stm32_F103C6_Drivers/%.c Stm32_F103C6_Drivers/subdir.mk
	arm-none-eabi-gcc  -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I"C:/Users/ismail/Downloads/Micro_Essential_Peripheral/4.GPIO EXTI & Section/lab assignment/code/HAL/Inc" -I../Inc -I"C:/Users/ismail/Downloads/Micro_Essential_Peripheral/4.GPIO EXTI & Section/lab assignment/code/CMSIS" -I"C:/Users/ismail/Downloads/Micro_Essential_Peripheral/4.GPIO EXTI & Section/lab assignment/code/Stm32_F103C6_Drivers/Inc" -I"C:/Users/ismail/Downloads/Micro_Essential_Peripheral/4.GPIO EXTI & Section/lab assignment/code/MY_RTOS/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Stm32_F103C6_Drivers

clean-Stm32_F103C6_Drivers:
	-$(RM) ./Stm32_F103C6_Drivers/EXTI.cyclo ./Stm32_F103C6_Drivers/EXTI.d ./Stm32_F103C6_Drivers/EXTI.o ./Stm32_F103C6_Drivers/EXTI.su ./Stm32_F103C6_Drivers/GPIO.cyclo ./Stm32_F103C6_Drivers/GPIO.d ./Stm32_F103C6_Drivers/GPIO.o ./Stm32_F103C6_Drivers/GPIO.su

.PHONY: clean-Stm32_F103C6_Drivers
