################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/opcodes/advanced/Syscall/SysCall.cpp 

OBJS += \
./src/opcodes/advanced/Syscall/SysCall.o 

CPP_DEPS += \
./src/opcodes/advanced/Syscall/SysCall.d 


# Each subdirectory must supply rules for building sources it contributes
src/opcodes/advanced/Syscall/%.o: ../src/opcodes/advanced/Syscall/%.cpp src/opcodes/advanced/Syscall/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O1 -g3 -Wall -c -fmessage-length=0 -fpermissive -m64 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


