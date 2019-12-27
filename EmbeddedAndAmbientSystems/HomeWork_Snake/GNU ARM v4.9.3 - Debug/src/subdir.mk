################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/DisplayFunctions.c \
../src/GameFunctions.c \
../src/InitDevice.c \
../src/main.c \
../src/segmentlcd.c 

OBJS += \
./src/DisplayFunctions.o \
./src/GameFunctions.o \
./src/InitDevice.o \
./src/main.o \
./src/segmentlcd.o 

C_DEPS += \
./src/DisplayFunctions.d \
./src/GameFunctions.d \
./src/InitDevice.d \
./src/main.d \
./src/segmentlcd.d 


# Each subdirectory must supply rules for building sources it contributes
src/DisplayFunctions.o: ../src/DisplayFunctions.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb -std=c99 '-DEFM32GG990F1024=1' '-DDEBUG=1' -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v1.1//platform/CMSIS/Include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v1.1//platform/emlib/inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v1.1//hardware/kit/common/drivers" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v1.1//platform/Device/SiliconLabs/EFM32GG/Include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v1.1//hardware/kit/EFM32GG_STK3700/config" -I"D:/SimplicityStudioWorkspace/Snake/inc" -include"D:\SimplicityStudioWorkspace\Snake\inc\DisplayFunctions.h" -include"D:\SimplicityStudioWorkspace\Snake\inc\GameFunctions.h" -include"D:\SimplicityStudioWorkspace\Snake\inc\InitDevice.h" -include"D:\SimplicityStudioWorkspace\Snake\inc\mytype.h" -include"D:\SimplicityStudioWorkspace\Snake\inc\segmentlcd_spec.h" -include"D:\SimplicityStudioWorkspace\Snake\inc\segmentlcd.h" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -MMD -MP -MF"src/DisplayFunctions.d" -MT"src/DisplayFunctions.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/GameFunctions.o: ../src/GameFunctions.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb -std=c99 '-DEFM32GG990F1024=1' '-DDEBUG=1' -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v1.1//platform/CMSIS/Include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v1.1//platform/emlib/inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v1.1//hardware/kit/common/drivers" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v1.1//platform/Device/SiliconLabs/EFM32GG/Include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v1.1//hardware/kit/EFM32GG_STK3700/config" -I"D:/SimplicityStudioWorkspace/Snake/inc" -include"D:\SimplicityStudioWorkspace\Snake\inc\DisplayFunctions.h" -include"D:\SimplicityStudioWorkspace\Snake\inc\GameFunctions.h" -include"D:\SimplicityStudioWorkspace\Snake\inc\InitDevice.h" -include"D:\SimplicityStudioWorkspace\Snake\inc\mytype.h" -include"D:\SimplicityStudioWorkspace\Snake\inc\segmentlcd_spec.h" -include"D:\SimplicityStudioWorkspace\Snake\inc\segmentlcd.h" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -MMD -MP -MF"src/GameFunctions.d" -MT"src/GameFunctions.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/InitDevice.o: ../src/InitDevice.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb -std=c99 '-DEFM32GG990F1024=1' '-DDEBUG=1' -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v1.1//platform/CMSIS/Include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v1.1//platform/emlib/inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v1.1//hardware/kit/common/drivers" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v1.1//platform/Device/SiliconLabs/EFM32GG/Include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v1.1//hardware/kit/EFM32GG_STK3700/config" -I"D:/SimplicityStudioWorkspace/Snake/inc" -include"D:\SimplicityStudioWorkspace\Snake\inc\DisplayFunctions.h" -include"D:\SimplicityStudioWorkspace\Snake\inc\GameFunctions.h" -include"D:\SimplicityStudioWorkspace\Snake\inc\InitDevice.h" -include"D:\SimplicityStudioWorkspace\Snake\inc\mytype.h" -include"D:\SimplicityStudioWorkspace\Snake\inc\segmentlcd_spec.h" -include"D:\SimplicityStudioWorkspace\Snake\inc\segmentlcd.h" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -MMD -MP -MF"src/InitDevice.d" -MT"src/InitDevice.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/main.o: ../src/main.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb -std=c99 '-DEFM32GG990F1024=1' '-DDEBUG=1' -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v1.1//platform/CMSIS/Include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v1.1//platform/emlib/inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v1.1//hardware/kit/common/drivers" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v1.1//platform/Device/SiliconLabs/EFM32GG/Include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v1.1//hardware/kit/EFM32GG_STK3700/config" -I"D:/SimplicityStudioWorkspace/Snake/inc" -include"D:\SimplicityStudioWorkspace\Snake\inc\DisplayFunctions.h" -include"D:\SimplicityStudioWorkspace\Snake\inc\GameFunctions.h" -include"D:\SimplicityStudioWorkspace\Snake\inc\InitDevice.h" -include"D:\SimplicityStudioWorkspace\Snake\inc\mytype.h" -include"D:\SimplicityStudioWorkspace\Snake\inc\segmentlcd_spec.h" -include"D:\SimplicityStudioWorkspace\Snake\inc\segmentlcd.h" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -MMD -MP -MF"src/main.d" -MT"src/main.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/segmentlcd.o: ../src/segmentlcd.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb -std=c99 '-DEFM32GG990F1024=1' '-DDEBUG=1' -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v1.1//platform/CMSIS/Include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v1.1//platform/emlib/inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v1.1//hardware/kit/common/drivers" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v1.1//platform/Device/SiliconLabs/EFM32GG/Include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v1.1//hardware/kit/EFM32GG_STK3700/config" -I"D:/SimplicityStudioWorkspace/Snake/inc" -include"D:\SimplicityStudioWorkspace\Snake\inc\DisplayFunctions.h" -include"D:\SimplicityStudioWorkspace\Snake\inc\GameFunctions.h" -include"D:\SimplicityStudioWorkspace\Snake\inc\InitDevice.h" -include"D:\SimplicityStudioWorkspace\Snake\inc\mytype.h" -include"D:\SimplicityStudioWorkspace\Snake\inc\segmentlcd_spec.h" -include"D:\SimplicityStudioWorkspace\Snake\inc\segmentlcd.h" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -MMD -MP -MF"src/segmentlcd.d" -MT"src/segmentlcd.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


