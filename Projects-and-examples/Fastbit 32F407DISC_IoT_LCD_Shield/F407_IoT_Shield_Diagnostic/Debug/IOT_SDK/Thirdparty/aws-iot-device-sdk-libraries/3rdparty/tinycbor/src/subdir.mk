################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/3rdparty/tinycbor/src/cborencoder.c \
../IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/3rdparty/tinycbor/src/cborencoder_close_container_checked.c \
../IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/3rdparty/tinycbor/src/cborerrorstrings.c \
../IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/3rdparty/tinycbor/src/cborparser.c \
../IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/3rdparty/tinycbor/src/cborparser_dup_string.c \
../IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/3rdparty/tinycbor/src/cborpretty.c \
../IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/3rdparty/tinycbor/src/cborpretty_stdio.c \
../IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/3rdparty/tinycbor/src/cbortojson.c \
../IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/3rdparty/tinycbor/src/cborvalidation.c 

OBJS += \
./IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/3rdparty/tinycbor/src/cborencoder.o \
./IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/3rdparty/tinycbor/src/cborencoder_close_container_checked.o \
./IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/3rdparty/tinycbor/src/cborerrorstrings.o \
./IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/3rdparty/tinycbor/src/cborparser.o \
./IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/3rdparty/tinycbor/src/cborparser_dup_string.o \
./IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/3rdparty/tinycbor/src/cborpretty.o \
./IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/3rdparty/tinycbor/src/cborpretty_stdio.o \
./IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/3rdparty/tinycbor/src/cbortojson.o \
./IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/3rdparty/tinycbor/src/cborvalidation.o 

C_DEPS += \
./IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/3rdparty/tinycbor/src/cborencoder.d \
./IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/3rdparty/tinycbor/src/cborencoder_close_container_checked.d \
./IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/3rdparty/tinycbor/src/cborerrorstrings.d \
./IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/3rdparty/tinycbor/src/cborparser.d \
./IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/3rdparty/tinycbor/src/cborparser_dup_string.d \
./IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/3rdparty/tinycbor/src/cborpretty.d \
./IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/3rdparty/tinycbor/src/cborpretty_stdio.d \
./IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/3rdparty/tinycbor/src/cbortojson.d \
./IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/3rdparty/tinycbor/src/cborvalidation.d 


# Each subdirectory must supply rules for building sources it contributes
IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/3rdparty/tinycbor/src/%.o IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/3rdparty/tinycbor/src/%.su IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/3rdparty/tinycbor/src/%.cyclo: ../IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/3rdparty/tinycbor/src/%.c IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/3rdparty/tinycbor/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/bhara/STM32CubeIDE/git local/fastbit-stm32WB-IOT-board/Projects-and-examples/f407_shield_test/Core/Src" -I"C:/Users/bhara/STM32CubeIDE/git local/fastbit-stm32WB-IOT-board/Projects-and-examples/f407_shield_test/IOT_SDK/BSP" -I"C:/Users/bhara/STM32CubeIDE/git local/fastbit-stm32WB-IOT-board/Projects-and-examples/f407_shield_test/IOT_SDK/BSP/utils" -I"C:/Users/bhara/STM32CubeIDE/git local/fastbit-stm32WB-IOT-board/Projects-and-examples/f407_shield_test/IOT_SDK/config" -I"C:/Users/bhara/STM32CubeIDE/git local/fastbit-stm32WB-IOT-board/Projects-and-examples/f407_shield_test/IOT_SDK/mqtt_helper" -I"C:/Users/bhara/STM32CubeIDE/git local/fastbit-stm32WB-IOT-board/Projects-and-examples/f407_shield_test/IOT_SDK/Thirdparty/FreeRTOS-Kernel/include" -I"C:/Users/bhara/STM32CubeIDE/git local/fastbit-stm32WB-IOT-board/Projects-and-examples/f407_shield_test/IOT_SDK/Thirdparty/FreeRTOS-Kernel/portable/GCC/ARM_CM4F" -I"C:/Users/bhara/STM32CubeIDE/git local/fastbit-stm32WB-IOT-board/Projects-and-examples/f407_shield_test/IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/standard/coreJSON/source/include" -I"C:/Users/bhara/STM32CubeIDE/git local/fastbit-stm32WB-IOT-board/Projects-and-examples/f407_shield_test/IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/standard/logging-stack" -I"C:/Users/bhara/STM32CubeIDE/git local/fastbit-stm32WB-IOT-board/Projects-and-examples/f407_shield_test/IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/aws/aws-iot-core-mqtt-file-streams/source/include" -I"C:/Users/bhara/STM32CubeIDE/git local/fastbit-stm32WB-IOT-board/Projects-and-examples/f407_shield_test/IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/3rdparty/tinycbor/src" -I"C:/Users/bhara/STM32CubeIDE/git local/fastbit-stm32WB-IOT-board/Projects-and-examples/f407_shield_test/IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/aws/Jobs-for-AWS-IoT-embedded-sdk/source/include" -I"C:/Users/bhara/STM32CubeIDE/git local/fastbit-stm32WB-IOT-board/Projects-and-examples/f407_shield_test/IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/aws/Jobs-for-AWS-IoT-embedded-sdk/source/otaJobParser/include" -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I"C:/Users/bhara/STM32CubeIDE/git local/fastbit-stm32WB-IOT-board/Projects-and-examples/f407_shield_test" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-IOT_SDK-2f-Thirdparty-2f-aws-2d-iot-2d-device-2d-sdk-2d-libraries-2f-3rdparty-2f-tinycbor-2f-src

clean-IOT_SDK-2f-Thirdparty-2f-aws-2d-iot-2d-device-2d-sdk-2d-libraries-2f-3rdparty-2f-tinycbor-2f-src:
	-$(RM) ./IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/3rdparty/tinycbor/src/cborencoder.cyclo ./IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/3rdparty/tinycbor/src/cborencoder.d ./IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/3rdparty/tinycbor/src/cborencoder.o ./IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/3rdparty/tinycbor/src/cborencoder.su ./IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/3rdparty/tinycbor/src/cborencoder_close_container_checked.cyclo ./IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/3rdparty/tinycbor/src/cborencoder_close_container_checked.d ./IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/3rdparty/tinycbor/src/cborencoder_close_container_checked.o ./IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/3rdparty/tinycbor/src/cborencoder_close_container_checked.su ./IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/3rdparty/tinycbor/src/cborerrorstrings.cyclo ./IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/3rdparty/tinycbor/src/cborerrorstrings.d ./IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/3rdparty/tinycbor/src/cborerrorstrings.o ./IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/3rdparty/tinycbor/src/cborerrorstrings.su ./IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/3rdparty/tinycbor/src/cborparser.cyclo ./IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/3rdparty/tinycbor/src/cborparser.d ./IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/3rdparty/tinycbor/src/cborparser.o ./IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/3rdparty/tinycbor/src/cborparser.su ./IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/3rdparty/tinycbor/src/cborparser_dup_string.cyclo ./IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/3rdparty/tinycbor/src/cborparser_dup_string.d ./IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/3rdparty/tinycbor/src/cborparser_dup_string.o ./IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/3rdparty/tinycbor/src/cborparser_dup_string.su ./IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/3rdparty/tinycbor/src/cborpretty.cyclo ./IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/3rdparty/tinycbor/src/cborpretty.d ./IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/3rdparty/tinycbor/src/cborpretty.o ./IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/3rdparty/tinycbor/src/cborpretty.su ./IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/3rdparty/tinycbor/src/cborpretty_stdio.cyclo ./IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/3rdparty/tinycbor/src/cborpretty_stdio.d ./IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/3rdparty/tinycbor/src/cborpretty_stdio.o ./IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/3rdparty/tinycbor/src/cborpretty_stdio.su ./IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/3rdparty/tinycbor/src/cbortojson.cyclo ./IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/3rdparty/tinycbor/src/cbortojson.d ./IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/3rdparty/tinycbor/src/cbortojson.o ./IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/3rdparty/tinycbor/src/cbortojson.su ./IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/3rdparty/tinycbor/src/cborvalidation.cyclo ./IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/3rdparty/tinycbor/src/cborvalidation.d ./IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/3rdparty/tinycbor/src/cborvalidation.o ./IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/3rdparty/tinycbor/src/cborvalidation.su

.PHONY: clean-IOT_SDK-2f-Thirdparty-2f-aws-2d-iot-2d-device-2d-sdk-2d-libraries-2f-3rdparty-2f-tinycbor-2f-src

