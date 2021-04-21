################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/asmjit/src/asmjit/x86/x86assembler.cpp \
../src/asmjit/src/asmjit/x86/x86builder.cpp \
../src/asmjit/src/asmjit/x86/x86compiler.cpp \
../src/asmjit/src/asmjit/x86/x86emithelper.cpp \
../src/asmjit/src/asmjit/x86/x86features.cpp \
../src/asmjit/src/asmjit/x86/x86formatter.cpp \
../src/asmjit/src/asmjit/x86/x86func.cpp \
../src/asmjit/src/asmjit/x86/x86instapi.cpp \
../src/asmjit/src/asmjit/x86/x86instdb.cpp \
../src/asmjit/src/asmjit/x86/x86operand.cpp \
../src/asmjit/src/asmjit/x86/x86rapass.cpp 

OBJS += \
./src/asmjit/src/asmjit/x86/x86assembler.o \
./src/asmjit/src/asmjit/x86/x86builder.o \
./src/asmjit/src/asmjit/x86/x86compiler.o \
./src/asmjit/src/asmjit/x86/x86emithelper.o \
./src/asmjit/src/asmjit/x86/x86features.o \
./src/asmjit/src/asmjit/x86/x86formatter.o \
./src/asmjit/src/asmjit/x86/x86func.o \
./src/asmjit/src/asmjit/x86/x86instapi.o \
./src/asmjit/src/asmjit/x86/x86instdb.o \
./src/asmjit/src/asmjit/x86/x86operand.o \
./src/asmjit/src/asmjit/x86/x86rapass.o 

CPP_DEPS += \
./src/asmjit/src/asmjit/x86/x86assembler.d \
./src/asmjit/src/asmjit/x86/x86builder.d \
./src/asmjit/src/asmjit/x86/x86compiler.d \
./src/asmjit/src/asmjit/x86/x86emithelper.d \
./src/asmjit/src/asmjit/x86/x86features.d \
./src/asmjit/src/asmjit/x86/x86formatter.d \
./src/asmjit/src/asmjit/x86/x86func.d \
./src/asmjit/src/asmjit/x86/x86instapi.d \
./src/asmjit/src/asmjit/x86/x86instdb.d \
./src/asmjit/src/asmjit/x86/x86operand.d \
./src/asmjit/src/asmjit/x86/x86rapass.d 


# Each subdirectory must supply rules for building sources it contributes
src/asmjit/src/asmjit/x86/%.o: ../src/asmjit/src/asmjit/x86/%.cpp src/asmjit/src/asmjit/x86/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O1 -g3 -Wall -c -fmessage-length=0 -fpermissive -m64 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


