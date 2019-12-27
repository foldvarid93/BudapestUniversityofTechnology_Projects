################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include emlib/subdir.mk
-include Drivers/subdir.mk
-include CMSIS/EFM32GG/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: displaySegmentField.axf

# Tool invocations
displaySegmentField.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU ARM C Linker'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb -T "displaySegmentField.ld" -Xlinker --gc-sections -Xlinker -Map="displaySegmentField.map" --specs=nano.specs -o displaySegmentField.axf "./CMSIS/EFM32GG/startup_efm32gg.o" "./CMSIS/EFM32GG/system_efm32gg.o" "./Drivers/segmentlcd.o" "./emlib/em_assert.o" "./emlib/em_cmu.o" "./emlib/em_emu.o" "./emlib/em_gpio.o" "./emlib/em_lcd.o" "./emlib/em_system.o" "./src/InitDevice.o" "./src/main.o" -Wl,--start-group -lgcc -lc -lnosys -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

	@echo 'Building hex file: displaySegmentField.hex'
	arm-none-eabi-objcopy -O ihex "displaySegmentField.axf" "displaySegmentField.hex"
	@echo ' '

	@echo 'Building bin file: displaySegmentField.bin'
	arm-none-eabi-objcopy -O binary "displaySegmentField.axf" "displaySegmentField.bin"
	@echo ' '

	@echo 'Building s37 file: displaySegmentField.s37'
	arm-none-eabi-objcopy -O srec "displaySegmentField.axf" "displaySegmentField.s37"
	@echo ' '

	@echo 'Running size tool'
	arm-none-eabi-size "displaySegmentField.axf"
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) displaySegmentField.axf
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
