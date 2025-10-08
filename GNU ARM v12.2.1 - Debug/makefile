################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include gecko_sdk_4.4.6/platform/service/system/src/subdir.mk
-include gecko_sdk_4.4.6/platform/service/device_init/src/subdir.mk
-include gecko_sdk_4.4.6/platform/emlib/src/subdir.mk
-include gecko_sdk_4.4.6/platform/common/toolchain/src/subdir.mk
-include gecko_sdk_4.4.6/platform/common/src/subdir.mk
-include gecko_sdk_4.4.6/platform/Device/SiliconLabs/EFM32GG11B/Source/subdir.mk
-include autogen/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := NAVCOM_Functionality_Testing
BUILD_ARTIFACT_EXTENSION := axf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: main-build

# Main-build Target
main-build: NAVCOM_Functionality_Testing.axf

# Tool invocations
NAVCOM_Functionality_Testing.axf: $(OBJS) $(USER_OBJS) makefile objects.mk $(OPTIONAL_TOOL_DEPS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU ARM C Linker'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m4 -mthumb -T "C:\Users\JonathanStorey\SimplicityStudio\v5_workspace\NAVCOM_Functionality_Testing\autogen\linkerfile.ld" -Wl,--no-warn-rwx-segments -Xlinker --gc-sections -Xlinker -Map="NAVCOM_Functionality_Testing.map" -mfpu=fpv4-sp-d16 -mfloat-abi=softfp --specs=nano.specs -o NAVCOM_Functionality_Testing.axf -Wl,--start-group "./autogen/sl_device_init_clocks.o" "./autogen/sl_event_handler.o" "./buzzer.o" "./em_timer.o" "./em_usart.o" "./ethernet_switch.o" "./helpers.o" "./hw_timer.o" "./i2c.o" "./initialisation.o" "./main.o" "./menu.o" "./usart.o" "./usart_expanders.o" "./gecko_sdk_4.4.6/platform/Device/SiliconLabs/EFM32GG11B/Source/startup_efm32gg11b.o" "./gecko_sdk_4.4.6/platform/Device/SiliconLabs/EFM32GG11B/Source/system_efm32gg11b.o" "./gecko_sdk_4.4.6/platform/common/src/sl_assert.o" "./gecko_sdk_4.4.6/platform/common/src/sl_syscalls.o" "./gecko_sdk_4.4.6/platform/common/toolchain/src/sl_memory.o" "./gecko_sdk_4.4.6/platform/emlib/src/em_adc.o" "./gecko_sdk_4.4.6/platform/emlib/src/em_cmu.o" "./gecko_sdk_4.4.6/platform/emlib/src/em_core.o" "./gecko_sdk_4.4.6/platform/emlib/src/em_emu.o" "./gecko_sdk_4.4.6/platform/emlib/src/em_gpio.o" "./gecko_sdk_4.4.6/platform/emlib/src/em_i2c.o" "./gecko_sdk_4.4.6/platform/emlib/src/em_msc.o" "./gecko_sdk_4.4.6/platform/emlib/src/em_system.o" "./gecko_sdk_4.4.6/platform/service/device_init/src/sl_device_init_emu_s1.o" "./gecko_sdk_4.4.6/platform/service/device_init/src/sl_device_init_nvic.o" "./gecko_sdk_4.4.6/platform/service/system/src/sl_system_init.o" "./gecko_sdk_4.4.6/platform/service/system/src/sl_system_process_action.o" -lgcc -lc -lm -lnosys -Wl,--end-group -Wl,--start-group -lgcc -lc -lnosys -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

	@echo 'Building out file: NAVCOM_Functionality_Testing.out'
	arm-none-eabi-objcopy "NAVCOM_Functionality_Testing.axf" "NAVCOM_Functionality_Testing.out"
	@echo ' '

	@echo 'Building hex file: NAVCOM_Functionality_Testing.hex'
	arm-none-eabi-objcopy -O ihex "NAVCOM_Functionality_Testing.axf" "NAVCOM_Functionality_Testing.hex"
	@echo ' '

	@echo 'Building bin file: NAVCOM_Functionality_Testing.bin'
	arm-none-eabi-objcopy -O binary "NAVCOM_Functionality_Testing.axf" "NAVCOM_Functionality_Testing.bin"
	@echo ' '

	@echo 'Building s37 file: NAVCOM_Functionality_Testing.s37'
	arm-none-eabi-objcopy -O srec "NAVCOM_Functionality_Testing.axf" "NAVCOM_Functionality_Testing.s37"
	@echo ' '

	@echo 'Running size tool'
	arm-none-eabi-size "NAVCOM_Functionality_Testing.axf" -A
	@echo ' '

# Other Targets
clean:
	-@$(foreach FILE, $(EXECUTABLES), $(shell $(RM) $(FILE)) )
	-@$(foreach FILE, $(OBJS), $(shell $(RM) $(FILE)) )
	-@$(foreach FILE, $(C_DEPS), $(shell $(RM) $(FILE)) )
	-$(RM) NAVCOM_Functionality_Testing.axf
	-@echo ' '

.PHONY: all clean dependents main-build

-include ../makefile.targets
