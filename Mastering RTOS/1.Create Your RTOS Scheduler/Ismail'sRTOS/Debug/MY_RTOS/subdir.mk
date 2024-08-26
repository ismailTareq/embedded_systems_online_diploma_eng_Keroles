################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MY_RTOS/Circular_FIFO.c \
../MY_RTOS/CortexMX_OS_porting.c \
../MY_RTOS/Scheduler.c 

OBJS += \
./MY_RTOS/Circular_FIFO.o \
./MY_RTOS/CortexMX_OS_porting.o \
./MY_RTOS/Scheduler.o 

C_DEPS += \
./MY_RTOS/Circular_FIFO.d \
./MY_RTOS/CortexMX_OS_porting.d \
./MY_RTOS/Scheduler.d 


# Each subdirectory must supply rules for building sources it contributes
MY_RTOS/%.o MY_RTOS/%.su MY_RTOS/%.cyclo: ../MY_RTOS/%.c MY_RTOS/subdir.mk
	arm-none-eabi-gcc  -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I"C:/Users/ismail/Downloads/Micro_Essential_Peripheral/4.GPIO EXTI & Section/lab assignment/code/HAL/Inc" -I../Inc -I"C:/Users/ismail/Downloads/Micro_Essential_Peripheral/4.GPIO EXTI & Section/lab assignment/code/CMSIS" -I"C:/Users/ismail/Downloads/Micro_Essential_Peripheral/4.GPIO EXTI & Section/lab assignment/code/Stm32_F103C6_Drivers/Inc" -I"C:/Users/ismail/Downloads/Micro_Essential_Peripheral/4.GPIO EXTI & Section/lab assignment/code/MY_RTOS/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-MY_RTOS

clean-MY_RTOS:
	-$(RM) ./MY_RTOS/Circular_FIFO.cyclo ./MY_RTOS/Circular_FIFO.d ./MY_RTOS/Circular_FIFO.o ./MY_RTOS/Circular_FIFO.su ./MY_RTOS/CortexMX_OS_porting.cyclo ./MY_RTOS/CortexMX_OS_porting.d ./MY_RTOS/CortexMX_OS_porting.o ./MY_RTOS/CortexMX_OS_porting.su ./MY_RTOS/Scheduler.cyclo ./MY_RTOS/Scheduler.d ./MY_RTOS/Scheduler.o ./MY_RTOS/Scheduler.su

.PHONY: clean-MY_RTOS

