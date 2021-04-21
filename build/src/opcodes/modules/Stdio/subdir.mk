################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/opcodes/modules/Stdio/ModuleSdtio.cpp 

OBJS += \
./src/opcodes/modules/Stdio/ModuleSdtio.o 

CPP_DEPS += \
./src/opcodes/modules/Stdio/ModuleSdtio.d 


# Each subdirectory must supply rules for building sources it contributes
src/opcodes/modules/Stdio/%.o: ../src/opcodes/modules/Stdio/%.cpp src/opcodes/modules/Stdio/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O1 -g3 -Wall -c -fmessage-length=0 -fpermissive -m64 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


