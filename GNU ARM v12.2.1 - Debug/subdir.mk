################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../buzzer.c \
C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2/platform/emlib/src/em_timer.c \
C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2/platform/emlib/src/em_usart.c \
../helpers.c \
../hw_timer.c \
../i2c.c \
../main.c \
../sw_delay.c \
../usart.c 

OBJS += \
./buzzer.o \
./em_timer.o \
./em_usart.o \
./helpers.o \
./hw_timer.o \
./i2c.o \
./main.o \
./sw_delay.o \
./usart.o 

C_DEPS += \
./buzzer.d \
./em_timer.d \
./em_usart.d \
./helpers.d \
./hw_timer.d \
./i2c.d \
./main.d \
./sw_delay.d \
./usart.d 


# Each subdirectory must supply rules for building sources it contributes
buzzer.o: ../buzzer.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 '-DDEBUG=1' '-DDEBUG_EFM=1' '-DEFM32GG11B420F2048GQ100=1' '-DSL_COMPONENT_CATALOG_PRESENT=1' -I"C:\Users\JonathanStorey\SimplicityStudio\v5_workspace\NAVCOM_Functionality_Testing\config" -I"C:\Users\JonathanStorey\SimplicityStudio\v5_workspace\NAVCOM_Functionality_Testing\autogen" -I"C:\Users\JonathanStorey\SimplicityStudio\v5_workspace\NAVCOM_Functionality_Testing" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/Device/SiliconLabs/EFM32GG11B/Include" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/CMSIS/Core/Include" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/service/device_init/inc" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/emlib/inc" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/common/inc" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/common/toolchain/inc" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/service/system/inc" -O0 -Wall -Wextra -mno-sched-prolog -fno-builtin -fomit-frame-pointer -ffunction-sections -fdata-sections -imacrossl_gcc_preinclude.h -mfpu=fpv4-sp-d16 -mfloat-abi=softfp --specs=nano.specs -c -fmessage-length=0 -MMD -MP -MF"buzzer.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

em_timer.o: C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2/platform/emlib/src/em_timer.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 '-DDEBUG=1' '-DDEBUG_EFM=1' '-DEFM32GG11B420F2048GQ100=1' '-DSL_COMPONENT_CATALOG_PRESENT=1' -I"C:\Users\JonathanStorey\SimplicityStudio\v5_workspace\NAVCOM_Functionality_Testing\config" -I"C:\Users\JonathanStorey\SimplicityStudio\v5_workspace\NAVCOM_Functionality_Testing\autogen" -I"C:\Users\JonathanStorey\SimplicityStudio\v5_workspace\NAVCOM_Functionality_Testing" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/Device/SiliconLabs/EFM32GG11B/Include" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/CMSIS/Core/Include" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/service/device_init/inc" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/emlib/inc" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/common/inc" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/common/toolchain/inc" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/service/system/inc" -O0 -Wall -Wextra -mno-sched-prolog -fno-builtin -fomit-frame-pointer -ffunction-sections -fdata-sections -imacrossl_gcc_preinclude.h -mfpu=fpv4-sp-d16 -mfloat-abi=softfp --specs=nano.specs -c -fmessage-length=0 -MMD -MP -MF"em_timer.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

em_usart.o: C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2/platform/emlib/src/em_usart.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 '-DDEBUG=1' '-DDEBUG_EFM=1' '-DEFM32GG11B420F2048GQ100=1' '-DSL_COMPONENT_CATALOG_PRESENT=1' -I"C:\Users\JonathanStorey\SimplicityStudio\v5_workspace\NAVCOM_Functionality_Testing\config" -I"C:\Users\JonathanStorey\SimplicityStudio\v5_workspace\NAVCOM_Functionality_Testing\autogen" -I"C:\Users\JonathanStorey\SimplicityStudio\v5_workspace\NAVCOM_Functionality_Testing" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/Device/SiliconLabs/EFM32GG11B/Include" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/CMSIS/Core/Include" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/service/device_init/inc" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/emlib/inc" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/common/inc" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/common/toolchain/inc" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/service/system/inc" -O0 -Wall -Wextra -mno-sched-prolog -fno-builtin -fomit-frame-pointer -ffunction-sections -fdata-sections -imacrossl_gcc_preinclude.h -mfpu=fpv4-sp-d16 -mfloat-abi=softfp --specs=nano.specs -c -fmessage-length=0 -MMD -MP -MF"em_usart.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

helpers.o: ../helpers.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 '-DDEBUG=1' '-DDEBUG_EFM=1' '-DEFM32GG11B420F2048GQ100=1' '-DSL_COMPONENT_CATALOG_PRESENT=1' -I"C:\Users\JonathanStorey\SimplicityStudio\v5_workspace\NAVCOM_Functionality_Testing\config" -I"C:\Users\JonathanStorey\SimplicityStudio\v5_workspace\NAVCOM_Functionality_Testing\autogen" -I"C:\Users\JonathanStorey\SimplicityStudio\v5_workspace\NAVCOM_Functionality_Testing" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/Device/SiliconLabs/EFM32GG11B/Include" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/CMSIS/Core/Include" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/service/device_init/inc" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/emlib/inc" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/common/inc" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/common/toolchain/inc" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/service/system/inc" -O0 -Wall -Wextra -mno-sched-prolog -fno-builtin -fomit-frame-pointer -ffunction-sections -fdata-sections -imacrossl_gcc_preinclude.h -mfpu=fpv4-sp-d16 -mfloat-abi=softfp --specs=nano.specs -c -fmessage-length=0 -MMD -MP -MF"helpers.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

hw_timer.o: ../hw_timer.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 '-DDEBUG=1' '-DDEBUG_EFM=1' '-DEFM32GG11B420F2048GQ100=1' '-DSL_COMPONENT_CATALOG_PRESENT=1' -I"C:\Users\JonathanStorey\SimplicityStudio\v5_workspace\NAVCOM_Functionality_Testing\config" -I"C:\Users\JonathanStorey\SimplicityStudio\v5_workspace\NAVCOM_Functionality_Testing\autogen" -I"C:\Users\JonathanStorey\SimplicityStudio\v5_workspace\NAVCOM_Functionality_Testing" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/Device/SiliconLabs/EFM32GG11B/Include" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/CMSIS/Core/Include" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/service/device_init/inc" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/emlib/inc" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/common/inc" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/common/toolchain/inc" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/service/system/inc" -O0 -Wall -Wextra -mno-sched-prolog -fno-builtin -fomit-frame-pointer -ffunction-sections -fdata-sections -imacrossl_gcc_preinclude.h -mfpu=fpv4-sp-d16 -mfloat-abi=softfp --specs=nano.specs -c -fmessage-length=0 -MMD -MP -MF"hw_timer.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

i2c.o: ../i2c.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 '-DDEBUG=1' '-DDEBUG_EFM=1' '-DEFM32GG11B420F2048GQ100=1' '-DSL_COMPONENT_CATALOG_PRESENT=1' -I"C:\Users\JonathanStorey\SimplicityStudio\v5_workspace\NAVCOM_Functionality_Testing\config" -I"C:\Users\JonathanStorey\SimplicityStudio\v5_workspace\NAVCOM_Functionality_Testing\autogen" -I"C:\Users\JonathanStorey\SimplicityStudio\v5_workspace\NAVCOM_Functionality_Testing" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/Device/SiliconLabs/EFM32GG11B/Include" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/CMSIS/Core/Include" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/service/device_init/inc" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/emlib/inc" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/common/inc" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/common/toolchain/inc" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/service/system/inc" -O0 -Wall -Wextra -mno-sched-prolog -fno-builtin -fomit-frame-pointer -ffunction-sections -fdata-sections -imacrossl_gcc_preinclude.h -mfpu=fpv4-sp-d16 -mfloat-abi=softfp --specs=nano.specs -c -fmessage-length=0 -MMD -MP -MF"i2c.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

main.o: ../main.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 '-DDEBUG=1' '-DDEBUG_EFM=1' '-DEFM32GG11B420F2048GQ100=1' '-DSL_COMPONENT_CATALOG_PRESENT=1' -I"C:\Users\JonathanStorey\SimplicityStudio\v5_workspace\NAVCOM_Functionality_Testing\config" -I"C:\Users\JonathanStorey\SimplicityStudio\v5_workspace\NAVCOM_Functionality_Testing\autogen" -I"C:\Users\JonathanStorey\SimplicityStudio\v5_workspace\NAVCOM_Functionality_Testing" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/Device/SiliconLabs/EFM32GG11B/Include" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/CMSIS/Core/Include" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/service/device_init/inc" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/emlib/inc" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/common/inc" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/common/toolchain/inc" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/service/system/inc" -O0 -Wall -Wextra -mno-sched-prolog -fno-builtin -fomit-frame-pointer -ffunction-sections -fdata-sections -imacrossl_gcc_preinclude.h -mfpu=fpv4-sp-d16 -mfloat-abi=softfp --specs=nano.specs -c -fmessage-length=0 -MMD -MP -MF"main.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

sw_delay.o: ../sw_delay.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 '-DDEBUG=1' '-DDEBUG_EFM=1' '-DEFM32GG11B420F2048GQ100=1' '-DSL_COMPONENT_CATALOG_PRESENT=1' -I"C:\Users\JonathanStorey\SimplicityStudio\v5_workspace\NAVCOM_Functionality_Testing\config" -I"C:\Users\JonathanStorey\SimplicityStudio\v5_workspace\NAVCOM_Functionality_Testing\autogen" -I"C:\Users\JonathanStorey\SimplicityStudio\v5_workspace\NAVCOM_Functionality_Testing" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/Device/SiliconLabs/EFM32GG11B/Include" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/CMSIS/Core/Include" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/service/device_init/inc" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/emlib/inc" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/common/inc" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/common/toolchain/inc" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/service/system/inc" -O0 -Wall -Wextra -mno-sched-prolog -fno-builtin -fomit-frame-pointer -ffunction-sections -fdata-sections -imacrossl_gcc_preinclude.h -mfpu=fpv4-sp-d16 -mfloat-abi=softfp --specs=nano.specs -c -fmessage-length=0 -MMD -MP -MF"sw_delay.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

usart.o: ../usart.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 '-DDEBUG=1' '-DDEBUG_EFM=1' '-DEFM32GG11B420F2048GQ100=1' '-DSL_COMPONENT_CATALOG_PRESENT=1' -I"C:\Users\JonathanStorey\SimplicityStudio\v5_workspace\NAVCOM_Functionality_Testing\config" -I"C:\Users\JonathanStorey\SimplicityStudio\v5_workspace\NAVCOM_Functionality_Testing\autogen" -I"C:\Users\JonathanStorey\SimplicityStudio\v5_workspace\NAVCOM_Functionality_Testing" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/Device/SiliconLabs/EFM32GG11B/Include" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/CMSIS/Core/Include" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/service/device_init/inc" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/emlib/inc" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/common/inc" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/common/toolchain/inc" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/service/system/inc" -O0 -Wall -Wextra -mno-sched-prolog -fno-builtin -fomit-frame-pointer -ffunction-sections -fdata-sections -imacrossl_gcc_preinclude.h -mfpu=fpv4-sp-d16 -mfloat-abi=softfp --specs=nano.specs -c -fmessage-length=0 -MMD -MP -MF"usart.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


