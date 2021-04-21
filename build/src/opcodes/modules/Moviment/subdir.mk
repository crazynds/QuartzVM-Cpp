################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/opcodes/modules/Moviment/ModuleMoviment.cpp \
../src/opcodes/modules/Moviment/cmov.cpp \
../src/opcodes/modules/Moviment/mov.cpp 

OBJS += \
./src/opcodes/modules/Moviment/ModuleMoviment.o \
./src/opcodes/modules/Moviment/cmov.o \
./src/opcodes/modules/Moviment/mov.o 

CPP_DEPS += \
./src/opcodes/modules/Moviment/ModuleMoviment.d \
./src/opcodes/modules/Moviment/cmov.d \
./src/opcodes/modules/Moviment/mov.d 


# Each subdirectory must supply rules for building sources it contributes
src/opcodes/modules/Moviment/%.o: ../src/opcodes/modules/Moviment/%.cpp src/opcodes/modules/Moviment/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O1 -g3 -Wall -c -fmessage-length=0 -fpermissive -m64 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


