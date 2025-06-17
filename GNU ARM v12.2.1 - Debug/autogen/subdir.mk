################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../autogen/sl_device_init_clocks.c \
../autogen/sl_event_handler.c 

OBJS += \
./autogen/sl_device_init_clocks.o \
./autogen/sl_event_handler.o 

C_DEPS += \
./autogen/sl_device_init_clocks.d \
./autogen/sl_event_handler.d 


# Each subdirectory must supply rules for building sources it contributes
autogen/sl_device_init_clocks.o: ../autogen/sl_device_init_clocks.c autogen/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 '-DDEBUG=1' '-DDEBUG_EFM=1' '-DEFM32GG11B420F2048GQ100=1' '-DSL_COMPONENT_CATALOG_PRESENT=1' -I"C:\Users\JonathanStorey\SimplicityStudio\v5_workspace\NAVCOM_Functionality_Testing\config" -I"C:\Users\JonathanStorey\SimplicityStudio\v5_workspace\NAVCOM_Functionality_Testing\autogen" -I"C:\Users\JonathanStorey\SimplicityStudio\v5_workspace\NAVCOM_Functionality_Testing" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/Device/SiliconLabs/EFM32GG11B/Include" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/CMSIS/Core/Include" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/service/device_init/inc" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/emlib/inc" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/common/inc" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/common/toolchain/inc" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/service/system/inc" -O0 -Wall -Wextra -mno-sched-prolog -fno-builtin -fomit-frame-pointer -ffunction-sections -fdata-sections -imacrossl_gcc_preinclude.h -mfpu=fpv4-sp-d16 -mfloat-abi=softfp --specs=nano.specs -c -fmessage-length=0 -MMD -MP -MF"autogen/sl_device_init_clocks.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

autogen/sl_event_handler.o: ../autogen/sl_event_handler.c autogen/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 '-DDEBUG=1' '-DDEBUG_EFM=1' '-DEFM32GG11B420F2048GQ100=1' '-DSL_COMPONENT_CATALOG_PRESENT=1' -I"C:\Users\JonathanStorey\SimplicityStudio\v5_workspace\NAVCOM_Functionality_Testing\config" -I"C:\Users\JonathanStorey\SimplicityStudio\v5_workspace\NAVCOM_Functionality_Testing\autogen" -I"C:\Users\JonathanStorey\SimplicityStudio\v5_workspace\NAVCOM_Functionality_Testing" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/Device/SiliconLabs/EFM32GG11B/Include" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/CMSIS/Core/Include" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/service/device_init/inc" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/emlib/inc" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/common/inc" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/common/toolchain/inc" -I"C:/Users/JonathanStorey/SimplicityStudio/SDKs/gecko_sdk_2//platform/service/system/inc" -O0 -Wall -Wextra -mno-sched-prolog -fno-builtin -fomit-frame-pointer -ffunction-sections -fdata-sections -imacrossl_gcc_preinclude.h -mfpu=fpv4-sp-d16 -mfloat-abi=softfp --specs=nano.specs -c -fmessage-length=0 -MMD -MP -MF"autogen/sl_event_handler.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


