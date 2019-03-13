################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := cs-rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include commonEclipse/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
practica3.hex \

SECONDARY_LIST += \
practica3.lst \

SECONDARY_SIZE += \
practica3.siz \


# All Target
all: practica3.elf secondary-outputs

# Tool invocations
practica3.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM Sourcery Windows GCC C Linker'
	arm-none-eabi-gcc -T"C:\hlocal\EclipseARMwspace\practica3\commonEclipse\ld_script_iic.ld" -nostartfiles -L"C:\software\electronica\ARM\EclipseARM\eclipse\/../sourcery-g++-lite-arm-2011.03/arm-none-eabi/lib" -L"C:\hlocal\EclipseARMwspace\practica3\commonEclipse" -L"C:\software\electronica\ARM\EclipseARM\eclipse\/../sourcery-g++-lite-arm-2011.03/lib/gcc/arm-none-eabi/4.5.2" -Wl,-Map,practica3.map -mcpu=arm7tdmi -g3 -gdwarf-2 -o "practica3.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

practica3.hex: practica3.elf
	@echo 'Invoking: ARM Sourcery Windows GNU Create Flash Image'
	arm-none-eabi-objcopy -O binary practica3.elf  "practica3.hex"
	@echo 'Finished building: $@'
	@echo ' '

practica3.lst: practica3.elf
	@echo 'Invoking: ARM Sourcery Windows GNU Create Listing'
	arm-none-eabi-objdump -h -S practica3.elf > "practica3.lst"
	@echo 'Finished building: $@'
	@echo ' '

practica3.siz: practica3.elf
	@echo 'Invoking: ARM Sourcery Windows GNU Print Size'
	arm-none-eabi-size  --format=berkeley practica3.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(SECONDARY_SIZE)$(OBJS)$(C_DEPS)$(ASM_DEPS)$(SECONDARY_FLASH)$(EXECUTABLES)$(SECONDARY_LIST)$(S_UPPER_DEPS) practica3.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
