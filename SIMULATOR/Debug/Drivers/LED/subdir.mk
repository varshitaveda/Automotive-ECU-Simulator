################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/LED/led.c 

OBJS += \
./Drivers/LED/led.o 

C_DEPS += \
./Drivers/LED/led.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/LED/%.o Drivers/LED/%.su Drivers/LED/%.cyclo: ../Drivers/LED/%.c Drivers/LED/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I"C:/Users/Veda Varshita A/STM32CubeIDE/workspace_1.18.1/ECU SIMULATOR/SIMULATOR/Drivers/LED" -I"C:/Users/Veda Varshita A/STM32CubeIDE/workspace_1.18.1/ECU SIMULATOR/SIMULATOR/Drivers/IGNITION" -I"C:/Users/Veda Varshita A/STM32CubeIDE/workspace_1.18.1/ECU SIMULATOR/SIMULATOR/Drivers/DISPLAY" -I"C:/Users/Veda Varshita A/STM32CubeIDE/workspace_1.18.1/ECU SIMULATOR/SIMULATOR/Drivers/ECU" -I"C:/Users/Veda Varshita A/STM32CubeIDE/workspace_1.18.1/ECU SIMULATOR/SIMULATOR/Drivers/VEHICLE" -I"C:/Users/Veda Varshita A/STM32CubeIDE/workspace_1.18.1/ECU SIMULATOR/SIMULATOR/Drivers/UART" -I"C:/Users/Veda Varshita A/STM32CubeIDE/workspace_1.18.1/ECU SIMULATOR/SIMULATOR/Drivers/GPIO" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Veda Varshita A/STM32CubeIDE/workspace_1.18.1/ECU SIMULATOR/SIMULATOR/Drivers/ssd1306" -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-LED

clean-Drivers-2f-LED:
	-$(RM) ./Drivers/LED/led.cyclo ./Drivers/LED/led.d ./Drivers/LED/led.o ./Drivers/LED/led.su

.PHONY: clean-Drivers-2f-LED

