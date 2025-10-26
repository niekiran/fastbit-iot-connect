################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Middlewares/Third_Party/FatFs/src/option/subdir.mk
-include Middlewares/Third_Party/FatFs/src/subdir.mk
-include IOT_SDK/mqtt_helper/subdir.mk
-include IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/standard/coreJSON/source/subdir.mk
-include IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/aws/aws-iot-core-mqtt-file-streams/source/subdir.mk
-include IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/aws/Jobs-for-AWS-IoT-embedded-sdk/source/otaJobParser/subdir.mk
-include IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/aws/Jobs-for-AWS-IoT-embedded-sdk/source/subdir.mk
-include IOT_SDK/Thirdparty/aws-iot-device-sdk-libraries/3rdparty/tinycbor/src/subdir.mk
-include IOT_SDK/Thirdparty/FreeRTOS-Kernel/portable/MemMang/subdir.mk
-include IOT_SDK/Thirdparty/FreeRTOS-Kernel/portable/GCC/ARM_CM4F/subdir.mk
-include IOT_SDK/Thirdparty/FreeRTOS-Kernel/subdir.mk
-include IOT_SDK/BSP/utils/subdir.mk
-include IOT_SDK/BSP/subdir.mk
-include FATFS/Target/subdir.mk
-include FATFS/App/subdir.mk
-include Drivers/STM32F4xx_HAL_Driver/Src/subdir.mk
-include Drivers/CMSIS/Device/ST/STM32F4xx/Include/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := F407_IoT_Shield_Diagnostic
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
F407_IoT_Shield_Diagnostic.elf \

MAP_FILES += \
F407_IoT_Shield_Diagnostic.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
F407_IoT_Shield_Diagnostic.list \


# All Target
all: main-build

# Main-build Target
main-build: F407_IoT_Shield_Diagnostic.elf secondary-outputs

# Tool invocations
F407_IoT_Shield_Diagnostic.elf F407_IoT_Shield_Diagnostic.map: $(OBJS) $(USER_OBJS) C:\Users\bhara\STM32CubeIDE\git\ local\fastbit-stm32WB-IOT-board\Projects-and-examples\f407_shield_test\STM32F407VGTX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "F407_IoT_Shield_Diagnostic.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"C:\Users\bhara\STM32CubeIDE\git local\fastbit-stm32WB-IOT-board\Projects-and-examples\f407_shield_test\STM32F407VGTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="F407_IoT_Shield_Diagnostic.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -u _printf_float -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

F407_IoT_Shield_Diagnostic.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "F407_IoT_Shield_Diagnostic.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) F407_IoT_Shield_Diagnostic.elf F407_IoT_Shield_Diagnostic.list F407_IoT_Shield_Diagnostic.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
