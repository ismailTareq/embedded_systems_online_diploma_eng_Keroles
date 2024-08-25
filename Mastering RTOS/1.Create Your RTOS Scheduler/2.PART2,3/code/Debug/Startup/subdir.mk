################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Startup/startup_stm32f103c6tx.s 

OBJS += \
./Startup/startup_stm32f103c6tx.o 

S_DEPS += \
./Startup/startup_stm32f103c6tx.d 


# Each subdirectory must supply rules for building sources it contributes
Startup/%.o: ../Startup/%.s Startup/subdir.mk
	arm-none-eabi-gcc  -gdwarf-2 -mcpu=cortex-m3 -g3 -c -I"C:/Users/ismail/Downloads/Micro_Essential_Peripheral/4.GPIO EXTI & Section/lab assignment/code/CMSIS" -I"C:/Users/ismail/Downloads/Micro_Essential_Peripheral/4.GPIO EXTI & Section/lab assignment/code/MY_RTOS/Inc" -I"C:/Users/ismail/Downloads/Micro_Essential_Peripheral/4.GPIO EXTI & Section/lab assignment/code/Stm32_F103C6_Drivers/Inc" -I"C:/Users/ismail/Downloads/Micro_Essential_Peripheral/4.GPIO EXTI & Section/lab assignment/code/HAL/Inc" -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"

clean: clean-Startup

clean-Startup:
	-$(RM) ./Startup/startup_stm32f103c6tx.d ./Startup/startup_stm32f103c6tx.o

.PHONY: clean-Startup

