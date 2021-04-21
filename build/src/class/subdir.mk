################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/class/Context.cpp \
../src/class/Thread.cpp 

OBJS += \
./src/class/Context.o \
./src/class/Thread.o 

CPP_DEPS += \
./src/class/Context.d \
./src/class/Thread.d 


# Each subdirectory must supply rules for building sources it contributes
src/class/%.o: ../src/class/%.cpp src/class/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O1 -g3 -Wall -c -fmessage-length=0 -fpermissive -m64 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


