################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := del

# All of the sources participating in the build are defined here
-include sources.mk
-include src/test/subdir.mk
-include src/opcodes/modules/Stdio/subdir.mk
-include src/opcodes/modules/Moviment/subdir.mk
-include src/opcodes/modules/Jit/subdir.mk
-include src/opcodes/basic/stack/subdir.mk
-include src/opcodes/basic/jmp/subdir.mk
-include src/opcodes/basic/calc/subdir.mk
-include src/opcodes/advanced/Syscall/subdir.mk
-include src/opcodes/advanced/Optimization/subdir.mk
-include src/opcodes/WordCoder/subdir.mk
-include src/lib/subdir.mk
-include src/class/VirtualMachine/subdir.mk
-include src/class/subdir.mk
-include src/asmjit/src/asmjit/x86/subdir.mk
-include src/asmjit/src/asmjit/core/subdir.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
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


BUILD_ARTIFACT_NAME := QuartzVM
BUILD_ARTIFACT_EXTENSION :=
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: QuartzVM

# Tool invocations
QuartzVM: $(OBJS) $(USER_OBJS) makefile objects.mk $(OPTIONAL_TOOL_DEPS)
	@echo 'Building target: $@'
	@echo 'Invoking: MinGW C++ Linker'
	g++  -o "QuartzVM" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(CC_DEPS)$(C++_DEPS)$(EXECUTABLES)$(OBJS)$(C_UPPER_DEPS)$(CXX_DEPS)$(CPP_DEPS)$(C_DEPS) QuartzVM
	-@echo ' '

.PHONY: all clean dependents

-include ../makefile.targets
