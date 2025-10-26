################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/aws/aws-iot-core-mqtt-file-streams/source/MQTTFileDownloader.c \
../IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/aws/aws-iot-core-mqtt-file-streams/source/MQTTFileDownloader_base64.c \
../IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/aws/aws-iot-core-mqtt-file-streams/source/MQTTFileDownloader_cbor.c 

OBJS += \
./IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/aws/aws-iot-core-mqtt-file-streams/source/MQTTFileDownloader.o \
./IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/aws/aws-iot-core-mqtt-file-streams/source/MQTTFileDownloader_base64.o \
./IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/aws/aws-iot-core-mqtt-file-streams/source/MQTTFileDownloader_cbor.o 

C_DEPS += \
./IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/aws/aws-iot-core-mqtt-file-streams/source/MQTTFileDownloader.d \
./IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/aws/aws-iot-core-mqtt-file-streams/source/MQTTFileDownloader_base64.d \
./IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/aws/aws-iot-core-mqtt-file-streams/source/MQTTFileDownloader_cbor.d 


# Each subdirectory must supply rules for building sources it contributes
IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/aws/aws-iot-core-mqtt-file-streams/source/%.o IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/aws/aws-iot-core-mqtt-file-streams/source/%.su IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/aws/aws-iot-core-mqtt-file-streams/source/%.cyclo: ../IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/aws/aws-iot-core-mqtt-file-streams/source/%.c IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/aws/aws-iot-core-mqtt-file-streams/source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/bhara/STM32CubeIDE/git local/fastbit-stm32WB-IOT-board/Projects-and-examples/f407_shield_test/Core/Src" -I"C:/Users/bhara/STM32CubeIDE/git local/fastbit-stm32WB-IOT-board/Projects-and-examples/f407_shield_test/IOT_SDK/BSP" -I"C:/Users/bhara/STM32CubeIDE/git local/fastbit-stm32WB-IOT-board/Projects-and-examples/f407_shield_test/IOT_SDK/BSP/utils" -I"C:/Users/bhara/STM32CubeIDE/git local/fastbit-stm32WB-IOT-board/Projects-and-examples/f407_shield_test/IOT_SDK/config" -I"C:/Users/bhara/STM32CubeIDE/git local/fastbit-stm32WB-IOT-board/Projects-and-examples/f407_shield_test/IOT_SDK/mqtt_helper" -I"C:/Users/bhara/STM32CubeIDE/git local/fastbit-stm32WB-IOT-board/Projects-and-examples/f407_shield_test/IOT_SDK/Thirdparty/FreeRTOS-Kernel/include" -I"C:/Users/bhara/STM32CubeIDE/git local/fastbit-stm32WB-IOT-board/Projects-and-examples/f407_shield_test/IOT_SDK/Thirdparty/FreeRTOS-Kernel/portable/GCC/ARM_CM4F" -I"C:/Users/bhara/STM32CubeIDE/git local/fastbit-stm32WB-IOT-board/Projects-and-examples/f407_shield_test/IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/standard/coreJSON/source/include" -I"C:/Users/bhara/STM32CubeIDE/git local/fastbit-stm32WB-IOT-board/Projects-and-examples/f407_shield_test/IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/standard/logging-stack" -I"C:/Users/bhara/STM32CubeIDE/git local/fastbit-stm32WB-IOT-board/Projects-and-examples/f407_shield_test/IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/aws/aws-iot-core-mqtt-file-streams/source/include" -I"C:/Users/bhara/STM32CubeIDE/git local/fastbit-stm32WB-IOT-board/Projects-and-examples/f407_shield_test/IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/3rdparty/tinycbor/src" -I"C:/Users/bhara/STM32CubeIDE/git local/fastbit-stm32WB-IOT-board/Projects-and-examples/f407_shield_test/IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/aws/Jobs-for-AWS-IoT-embedded-sdk/source/include" -I"C:/Users/bhara/STM32CubeIDE/git local/fastbit-stm32WB-IOT-board/Projects-and-examples/f407_shield_test/IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/aws/Jobs-for-AWS-IoT-embedded-sdk/source/otaJobParser/include" -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I"C:/Users/bhara/STM32CubeIDE/git local/fastbit-stm32WB-IOT-board/Projects-and-examples/f407_shield_test" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-IOT_SDK-2f-Thirdparty-2f-aws-2d-iot-2d-device-2d-sdk-2d-libraries-2f-aws-2f-aws-2d-iot-2d-core-2d-mqtt-2d-file-2d-streams-2f-source

clean-IOT_SDK-2f-Thirdparty-2f-aws-2d-iot-2d-device-2d-sdk-2d-libraries-2f-aws-2f-aws-2d-iot-2d-core-2d-mqtt-2d-file-2d-streams-2f-source:
	-$(RM) ./IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/aws/aws-iot-core-mqtt-file-streams/source/MQTTFileDownloader.cyclo ./IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/aws/aws-iot-core-mqtt-file-streams/source/MQTTFileDownloader.d ./IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/aws/aws-iot-core-mqtt-file-streams/source/MQTTFileDownloader.o ./IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/aws/aws-iot-core-mqtt-file-streams/source/MQTTFileDownloader.su ./IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/aws/aws-iot-core-mqtt-file-streams/source/MQTTFileDownloader_base64.cyclo ./IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/aws/aws-iot-core-mqtt-file-streams/source/MQTTFileDownloader_base64.d ./IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/aws/aws-iot-core-mqtt-file-streams/source/MQTTFileDownloader_base64.o ./IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/aws/aws-iot-core-mqtt-file-streams/source/MQTTFileDownloader_base64.su ./IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/aws/aws-iot-core-mqtt-file-streams/source/MQTTFileDownloader_cbor.cyclo ./IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/aws/aws-iot-core-mqtt-file-streams/source/MQTTFileDownloader_cbor.d ./IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/aws/aws-iot-core-mqtt-file-streams/source/MQTTFileDownloader_cbor.o ./IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/aws/aws-iot-core-mqtt-file-streams/source/MQTTFileDownloader_cbor.su

.PHONY: clean-IOT_SDK-2f-Thirdparty-2f-aws-2d-iot-2d-device-2d-sdk-2d-libraries-2f-aws-2f-aws-2d-iot-2d-core-2d-mqtt-2d-file-2d-streams-2f-source

