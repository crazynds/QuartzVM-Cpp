################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/lib/IOMessages.cpp \
../src/lib/Memory.cpp 

OBJS += \
./src/lib/IOMessages.o \
./src/lib/Memory.o 

CPP_DEPS += \
./src/lib/IOMessages.d \
./src/lib/Memory.d 


# Each subdirectory must supply rules for building sources it contributes
src/lib/%.o: ../src/lib/%.cpp src/lib/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O1 -g3 -Wall -c -fmessage-length=0 -fpermissive -m64 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


