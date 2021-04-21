################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/opcodes/basic/jmp/jmp.cpp 

OBJS += \
./src/opcodes/basic/jmp/jmp.o 

CPP_DEPS += \
./src/opcodes/basic/jmp/jmp.d 


# Each subdirectory must supply rules for building sources it contributes
src/opcodes/basic/jmp/%.o: ../src/opcodes/basic/jmp/%.cpp src/opcodes/basic/jmp/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O1 -g3 -Wall -c -fmessage-length=0 -fpermissive -m64 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


