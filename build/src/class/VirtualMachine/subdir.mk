################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/class/VirtualMachine/ManagerOpcodes.cpp \
../src/class/VirtualMachine/ManagerResources.cpp \
../src/class/VirtualMachine/VirtualMachine.cpp 

OBJS += \
./src/class/VirtualMachine/ManagerOpcodes.o \
./src/class/VirtualMachine/ManagerResources.o \
./src/class/VirtualMachine/VirtualMachine.o 

CPP_DEPS += \
./src/class/VirtualMachine/ManagerOpcodes.d \
./src/class/VirtualMachine/ManagerResources.d \
./src/class/VirtualMachine/VirtualMachine.d 


# Each subdirectory must supply rules for building sources it contributes
src/class/VirtualMachine/%.o: ../src/class/VirtualMachine/%.cpp src/class/VirtualMachine/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O1 -g3 -Wall -c -fmessage-length=0 -fpermissive -m64 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


