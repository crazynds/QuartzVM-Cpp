################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/opcodes/basic/stack/stack.cpp 

OBJS += \
./src/opcodes/basic/stack/stack.o 

CPP_DEPS += \
./src/opcodes/basic/stack/stack.d 


# Each subdirectory must supply rules for building sources it contributes
src/opcodes/basic/stack/%.o: ../src/opcodes/basic/stack/%.cpp src/opcodes/basic/stack/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O1 -g3 -Wall -c -fmessage-length=0 -fpermissive -m64 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


