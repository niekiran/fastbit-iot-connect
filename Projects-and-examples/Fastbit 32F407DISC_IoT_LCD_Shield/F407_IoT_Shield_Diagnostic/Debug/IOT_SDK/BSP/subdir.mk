################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../IOT_SDK/BSP/esp32_at.c \
../IOT_SDK/BSP/esp32_at_io.c \
../IOT_SDK/BSP/hdc1080.c \
../IOT_SDK/BSP/sh1106.c 

OBJS += \
./IOT_SDK/BSP/esp32_at.o \
./IOT_SDK/BSP/esp32_at_io.o \
./IOT_SDK/BSP/hdc1080.o \
./IOT_SDK/BSP/sh1106.o 

C_DEPS += \
./IOT_SDK/BSP/esp32_at.d \
./IOT_SDK/BSP/esp32_at_io.d \
./IOT_SDK/BSP/hdc1080.d \
./IOT_SDK/BSP/sh1106.d 


# Each subdirectory must supply rules for building sources it contributes
IOT_SDK/BSP/%.o IOT_SDK/BSP/%.su IOT_SDK/BSP/%.cyclo: ../IOT_SDK/BSP/%.c IOT_SDK/BSP/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/bhara/STM32CubeIDE/git local/fastbit-stm32WB-IOT-board/Projects-and-examples/f407_shield_test/Core/Src" -I"C:/Users/bhara/STM32CubeIDE/git local/fastbit-stm32WB-IOT-board/Projects-and-examples/f407_shield_test/IOT_SDK/BSP" -I"C:/Users/bhara/STM32CubeIDE/git local/fastbit-stm32WB-IOT-board/Projects-and-examples/f407_shield_test/IOT_SDK/BSP/utils" -I"C:/Users/bhara/STM32CubeIDE/git local/fastbit-stm32WB-IOT-board/Projects-and-examples/f407_shield_test/IOT_SDK/config" -I"C:/Users/bhara/STM32CubeIDE/git local/fastbit-stm32WB-IOT-board/Projects-and-examples/f407_shield_test/IOT_SDK/mqtt_helper" -I"C:/Users/bhara/STM32CubeIDE/git local/fastbit-stm32WB-IOT-board/Projects-and-examples/f407_shield_test/IOT_SDK/Thirdparty/FreeRTOS-Kernel/include" -I"C:/Users/bhara/STM32CubeIDE/git local/fastbit-stm32WB-IOT-board/Projects-and-examples/f407_shield_test/IOT_SDK/Thirdparty/FreeRTOS-Kernel/portable/GCC/ARM_CM4F" -I"C:/Users/bhara/STM32CubeIDE/git local/fastbit-stm32WB-IOT-board/Projects-and-examples/f407_shield_test/IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/standard/coreJSON/source/include" -I"C:/Users/bhara/STM32CubeIDE/git local/fastbit-stm32WB-IOT-board/Projects-and-examples/f407_shield_test/IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/standard/logging-stack" -I"C:/Users/bhara/STM32CubeIDE/git local/fastbit-stm32WB-IOT-board/Projects-and-examples/f407_shield_test/IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/aws/aws-iot-core-mqtt-file-streams/source/include" -I"C:/Users/bhara/STM32CubeIDE/git local/fastbit-stm32WB-IOT-board/Projects-and-examples/f407_shield_test/IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/3rdparty/tinycbor/src" -I"C:/Users/bhara/STM32CubeIDE/git local/fastbit-stm32WB-IOT-board/Projects-and-examples/f407_shield_test/IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/aws/Jobs-for-AWS-IoT-embedded-sdk/source/include" -I"C:/Users/bhara/STM32CubeIDE/git local/fastbit-stm32WB-IOT-board/Projects-and-examples/f407_shield_test/IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/aws/Jobs-for-AWS-IoT-embedded-sdk/source/otaJobParser/include" -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I"C:/Users/bhara/STM32CubeIDE/git local/fastbit-stm32WB-IOT-board/Projects-and-examples/f407_shield_test" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-IOT_SDK-2f-BSP

clean-IOT_SDK-2f-BSP:
	-$(RM) ./IOT_SDK/BSP/esp32_at.cyclo ./IOT_SDK/BSP/esp32_at.d ./IOT_SDK/BSP/esp32_at.o ./IOT_SDK/BSP/esp32_at.su ./IOT_SDK/BSP/esp32_at_io.cyclo ./IOT_SDK/BSP/esp32_at_io.d ./IOT_SDK/BSP/esp32_at_io.o ./IOT_SDK/BSP/esp32_at_io.su ./IOT_SDK/BSP/hdc1080.cyclo ./IOT_SDK/BSP/hdc1080.d ./IOT_SDK/BSP/hdc1080.o ./IOT_SDK/BSP/hdc1080.su ./IOT_SDK/BSP/sh1106.cyclo ./IOT_SDK/BSP/sh1106.d ./IOT_SDK/BSP/sh1106.o ./IOT_SDK/BSP/sh1106.su

.PHONY: clean-IOT_SDK-2f-BSP

