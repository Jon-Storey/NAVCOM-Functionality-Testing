################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2/platform/emlib/src/em_cmu.c \
C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2/platform/emlib/src/em_core.c \
C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2/platform/emlib/src/em_emu.c \
C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2/platform/emlib/src/em_gpio.c \
C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2/platform/emlib/src/em_i2c.c \
C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2/platform/emlib/src/em_msc.c \
C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2/platform/emlib/src/em_system.c 

OBJS += \
./gecko_sdk_4.4.6/platform/emlib/src/em_cmu.o \
./gecko_sdk_4.4.6/platform/emlib/src/em_core.o \
./gecko_sdk_4.4.6/platform/emlib/src/em_emu.o \
./gecko_sdk_4.4.6/platform/emlib/src/em_gpio.o \
./gecko_sdk_4.4.6/platform/emlib/src/em_i2c.o \
./gecko_sdk_4.4.6/platform/emlib/src/em_msc.o \
./gecko_sdk_4.4.6/platform/emlib/src/em_system.o 

C_DEPS += \
./gecko_sdk_4.4.6/platform/emlib/src/em_cmu.d \
./gecko_sdk_4.4.6/platform/emlib/src/em_core.d \
./gecko_sdk_4.4.6/platform/emlib/src/em_emu.d \
./gecko_sdk_4.4.6/platform/emlib/src/em_gpio.d \
./gecko_sdk_4.4.6/platform/emlib/src/em_i2c.d \
./gecko_sdk_4.4.6/platform/emlib/src/em_msc.d \
./gecko_sdk_4.4.6/platform/emlib/src/em_system.d 


# Each subdirectory must supply rules for building sources it contributes
gecko_sdk_4.4.6/platform/emlib/src/em_cmu.o: C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2/platform/emlib/src/em_cmu.c gecko_sdk_4.4.6/platform/emlib/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 '-DDEBUG=1' '-DDEBUG_EFM=1' '-DEFM32GG11B420F2048GQ100=1' '-DSL_COMPONENT_CATALOG_PRESENT=1' -I"C:\Users\JonathanStorey\SimplicityStudio\v5_workspace\NAVCOM_Functionality_Testing\config" -I"C:\Users\JonathanStorey\SimplicityStudio\v5_workspace\NAVCOM_Functionality_Testing\autogen" -I"C:\Users\JonathanStorey\SimplicityStudio\v5_workspace\NAVCOM_Functionality_Testing" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/Device/SiliconLabs/EFM32GG11B/Include" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/CMSIS/Core/Include" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/service/device_init/inc" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/emlib/inc" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/common/inc" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/common/toolchain/inc" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/service/system/inc" -O0 -Wall -Wextra -mno-sched-prolog -fno-builtin -fomit-frame-pointer -ffunction-sections -fdata-sections -imacrossl_gcc_preinclude.h -mfpu=fpv4-sp-d16 -mfloat-abi=softfp --specs=nano.specs -c -fmessage-length=0 -MMD -MP -MF"gecko_sdk_4.4.6/platform/emlib/src/em_cmu.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

gecko_sdk_4.4.6/platform/emlib/src/em_core.o: C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2/platform/emlib/src/em_core.c gecko_sdk_4.4.6/platform/emlib/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 '-DDEBUG=1' '-DDEBUG_EFM=1' '-DEFM32GG11B420F2048GQ100=1' '-DSL_COMPONENT_CATALOG_PRESENT=1' -I"C:\Users\JonathanStorey\SimplicityStudio\v5_workspace\NAVCOM_Functionality_Testing\config" -I"C:\Users\JonathanStorey\SimplicityStudio\v5_workspace\NAVCOM_Functionality_Testing\autogen" -I"C:\Users\JonathanStorey\SimplicityStudio\v5_workspace\NAVCOM_Functionality_Testing" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/Device/SiliconLabs/EFM32GG11B/Include" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/CMSIS/Core/Include" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/service/device_init/inc" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/emlib/inc" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/common/inc" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/common/toolchain/inc" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/service/system/inc" -O0 -Wall -Wextra -mno-sched-prolog -fno-builtin -fomit-frame-pointer -ffunction-sections -fdata-sections -imacrossl_gcc_preinclude.h -mfpu=fpv4-sp-d16 -mfloat-abi=softfp --specs=nano.specs -c -fmessage-length=0 -MMD -MP -MF"gecko_sdk_4.4.6/platform/emlib/src/em_core.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

gecko_sdk_4.4.6/platform/emlib/src/em_emu.o: C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2/platform/emlib/src/em_emu.c gecko_sdk_4.4.6/platform/emlib/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 '-DDEBUG=1' '-DDEBUG_EFM=1' '-DEFM32GG11B420F2048GQ100=1' '-DSL_COMPONENT_CATALOG_PRESENT=1' -I"C:\Users\JonathanStorey\SimplicityStudio\v5_workspace\NAVCOM_Functionality_Testing\config" -I"C:\Users\JonathanStorey\SimplicityStudio\v5_workspace\NAVCOM_Functionality_Testing\autogen" -I"C:\Users\JonathanStorey\SimplicityStudio\v5_workspace\NAVCOM_Functionality_Testing" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/Device/SiliconLabs/EFM32GG11B/Include" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/CMSIS/Core/Include" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/service/device_init/inc" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/emlib/inc" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/common/inc" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/common/toolchain/inc" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/service/system/inc" -O0 -Wall -Wextra -mno-sched-prolog -fno-builtin -fomit-frame-pointer -ffunction-sections -fdata-sections -imacrossl_gcc_preinclude.h -mfpu=fpv4-sp-d16 -mfloat-abi=softfp --specs=nano.specs -c -fmessage-length=0 -MMD -MP -MF"gecko_sdk_4.4.6/platform/emlib/src/em_emu.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

gecko_sdk_4.4.6/platform/emlib/src/em_gpio.o: C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2/platform/emlib/src/em_gpio.c gecko_sdk_4.4.6/platform/emlib/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 '-DDEBUG=1' '-DDEBUG_EFM=1' '-DEFM32GG11B420F2048GQ100=1' '-DSL_COMPONENT_CATALOG_PRESENT=1' -I"C:\Users\JonathanStorey\SimplicityStudio\v5_workspace\NAVCOM_Functionality_Testing\config" -I"C:\Users\JonathanStorey\SimplicityStudio\v5_workspace\NAVCOM_Functionality_Testing\autogen" -I"C:\Users\JonathanStorey\SimplicityStudio\v5_workspace\NAVCOM_Functionality_Testing" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/Device/SiliconLabs/EFM32GG11B/Include" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/CMSIS/Core/Include" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/service/device_init/inc" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/emlib/inc" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/common/inc" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/common/toolchain/inc" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/service/system/inc" -O0 -Wall -Wextra -mno-sched-prolog -fno-builtin -fomit-frame-pointer -ffunction-sections -fdata-sections -imacrossl_gcc_preinclude.h -mfpu=fpv4-sp-d16 -mfloat-abi=softfp --specs=nano.specs -c -fmessage-length=0 -MMD -MP -MF"gecko_sdk_4.4.6/platform/emlib/src/em_gpio.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

gecko_sdk_4.4.6/platform/emlib/src/em_i2c.o: C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2/platform/emlib/src/em_i2c.c gecko_sdk_4.4.6/platform/emlib/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 '-DDEBUG=1' '-DDEBUG_EFM=1' '-DEFM32GG11B420F2048GQ100=1' '-DSL_COMPONENT_CATALOG_PRESENT=1' -I"C:\Users\JonathanStorey\SimplicityStudio\v5_workspace\NAVCOM_Functionality_Testing\config" -I"C:\Users\JonathanStorey\SimplicityStudio\v5_workspace\NAVCOM_Functionality_Testing\autogen" -I"C:\Users\JonathanStorey\SimplicityStudio\v5_workspace\NAVCOM_Functionality_Testing" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/Device/SiliconLabs/EFM32GG11B/Include" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/CMSIS/Core/Include" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/service/device_init/inc" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/emlib/inc" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/common/inc" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/common/toolchain/inc" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/service/system/inc" -O0 -Wall -Wextra -mno-sched-prolog -fno-builtin -fomit-frame-pointer -ffunction-sections -fdata-sections -imacrossl_gcc_preinclude.h -mfpu=fpv4-sp-d16 -mfloat-abi=softfp --specs=nano.specs -c -fmessage-length=0 -MMD -MP -MF"gecko_sdk_4.4.6/platform/emlib/src/em_i2c.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

gecko_sdk_4.4.6/platform/emlib/src/em_msc.o: C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2/platform/emlib/src/em_msc.c gecko_sdk_4.4.6/platform/emlib/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 '-DDEBUG=1' '-DDEBUG_EFM=1' '-DEFM32GG11B420F2048GQ100=1' '-DSL_COMPONENT_CATALOG_PRESENT=1' -I"C:\Users\JonathanStorey\SimplicityStudio\v5_workspace\NAVCOM_Functionality_Testing\config" -I"C:\Users\JonathanStorey\SimplicityStudio\v5_workspace\NAVCOM_Functionality_Testing\autogen" -I"C:\Users\JonathanStorey\SimplicityStudio\v5_workspace\NAVCOM_Functionality_Testing" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/Device/SiliconLabs/EFM32GG11B/Include" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/CMSIS/Core/Include" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/service/device_init/inc" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/emlib/inc" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/common/inc" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/common/toolchain/inc" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/service/system/inc" -O0 -Wall -Wextra -mno-sched-prolog -fno-builtin -fomit-frame-pointer -ffunction-sections -fdata-sections -imacrossl_gcc_preinclude.h -mfpu=fpv4-sp-d16 -mfloat-abi=softfp --specs=nano.specs -c -fmessage-length=0 -MMD -MP -MF"gecko_sdk_4.4.6/platform/emlib/src/em_msc.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

gecko_sdk_4.4.6/platform/emlib/src/em_system.o: C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2/platform/emlib/src/em_system.c gecko_sdk_4.4.6/platform/emlib/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 '-DDEBUG=1' '-DDEBUG_EFM=1' '-DEFM32GG11B420F2048GQ100=1' '-DSL_COMPONENT_CATALOG_PRESENT=1' -I"C:\Users\JonathanStorey\SimplicityStudio\v5_workspace\NAVCOM_Functionality_Testing\config" -I"C:\Users\JonathanStorey\SimplicityStudio\v5_workspace\NAVCOM_Functionality_Testing\autogen" -I"C:\Users\JonathanStorey\SimplicityStudio\v5_workspace\NAVCOM_Functionality_Testing" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/Device/SiliconLabs/EFM32GG11B/Include" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/CMSIS/Core/Include" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/service/device_init/inc" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/emlib/inc" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/common/inc" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/common/toolchain/inc" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/service/system/inc" -O0 -Wall -Wextra -mno-sched-prolog -fno-builtin -fomit-frame-pointer -ffunction-sections -fdata-sections -imacrossl_gcc_preinclude.h -mfpu=fpv4-sp-d16 -mfloat-abi=softfp --specs=nano.specs -c -fmessage-length=0 -MMD -MP -MF"gecko_sdk_4.4.6/platform/emlib/src/em_system.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


