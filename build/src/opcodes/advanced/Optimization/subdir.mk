################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/opcodes/advanced/Optimization/optimized.cpp 

OBJS += \
./src/opcodes/advanced/Optimization/optimized.o 

CPP_DEPS += \
./src/opcodes/advanced/Optimization/optimized.d 


# Each subdirectory must supply rules for building sources it contributes
src/opcodes/advanced/Optimization/%.o: ../src/opcodes/advanced/Optimization/%.cpp src/opcodes/advanced/Optimization/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O1 -g3 -Wall -c -fmessage-length=0 -fpermissive -m64 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


