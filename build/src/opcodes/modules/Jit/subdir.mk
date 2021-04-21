################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/opcodes/modules/Jit/JitAuxiliar.cpp \
../src/opcodes/modules/Jit/ModuleJit.cpp \
../src/opcodes/modules/Jit/jit.cpp 

OBJS += \
./src/opcodes/modules/Jit/JitAuxiliar.o \
./src/opcodes/modules/Jit/ModuleJit.o \
./src/opcodes/modules/Jit/jit.o 

CPP_DEPS += \
./src/opcodes/modules/Jit/JitAuxiliar.d \
./src/opcodes/modules/Jit/ModuleJit.d \
./src/opcodes/modules/Jit/jit.d 


# Each subdirectory must supply rules for building sources it contributes
src/opcodes/modules/Jit/%.o: ../src/opcodes/modules/Jit/%.cpp src/opcodes/modules/Jit/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O1 -g3 -Wall -c -fmessage-length=0 -fpermissive -m64 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


