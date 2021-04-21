################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/opcodes/basic/calc/aritimetic1.cpp \
../src/opcodes/basic/calc/aritimetic2.cpp \
../src/opcodes/basic/calc/aritimetic3.cpp 

OBJS += \
./src/opcodes/basic/calc/aritimetic1.o \
./src/opcodes/basic/calc/aritimetic2.o \
./src/opcodes/basic/calc/aritimetic3.o 

CPP_DEPS += \
./src/opcodes/basic/calc/aritimetic1.d \
./src/opcodes/basic/calc/aritimetic2.d \
./src/opcodes/basic/calc/aritimetic3.d 


# Each subdirectory must supply rules for building sources it contributes
src/opcodes/basic/calc/%.o: ../src/opcodes/basic/calc/%.cpp src/opcodes/basic/calc/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O1 -g3 -Wall -c -fmessage-length=0 -fpermissive -m64 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


