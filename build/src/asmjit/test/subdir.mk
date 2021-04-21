################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/asmjit/test/asmjit_test_assembler.cpp \
../src/asmjit/test/asmjit_test_assembler_x64.cpp \
../src/asmjit/test/asmjit_test_assembler_x86.cpp \
../src/asmjit/test/asmjit_test_compiler.cpp \
../src/asmjit/test/asmjit_test_compiler_x86.cpp \
../src/asmjit/test/asmjit_test_emitters.cpp \
../src/asmjit/test/asmjit_test_instinfo.cpp \
../src/asmjit/test/asmjit_test_perf.cpp \
../src/asmjit/test/asmjit_test_perf_x86.cpp \
../src/asmjit/test/asmjit_test_unit.cpp \
../src/asmjit/test/asmjit_test_x86_sections.cpp \
../src/asmjit/test/broken.cpp 

OBJS += \
./src/asmjit/test/asmjit_test_assembler.o \
./src/asmjit/test/asmjit_test_assembler_x64.o \
./src/asmjit/test/asmjit_test_assembler_x86.o \
./src/asmjit/test/asmjit_test_compiler.o \
./src/asmjit/test/asmjit_test_compiler_x86.o \
./src/asmjit/test/asmjit_test_emitters.o \
./src/asmjit/test/asmjit_test_instinfo.o \
./src/asmjit/test/asmjit_test_perf.o \
./src/asmjit/test/asmjit_test_perf_x86.o \
./src/asmjit/test/asmjit_test_unit.o \
./src/asmjit/test/asmjit_test_x86_sections.o \
./src/asmjit/test/broken.o 

CPP_DEPS += \
./src/asmjit/test/asmjit_test_assembler.d \
./src/asmjit/test/asmjit_test_assembler_x64.d \
./src/asmjit/test/asmjit_test_assembler_x86.d \
./src/asmjit/test/asmjit_test_compiler.d \
./src/asmjit/test/asmjit_test_compiler_x86.d \
./src/asmjit/test/asmjit_test_emitters.d \
./src/asmjit/test/asmjit_test_instinfo.d \
./src/asmjit/test/asmjit_test_perf.d \
./src/asmjit/test/asmjit_test_perf_x86.d \
./src/asmjit/test/asmjit_test_unit.d \
./src/asmjit/test/asmjit_test_x86_sections.d \
./src/asmjit/test/broken.d 


# Each subdirectory must supply rules for building sources it contributes
src/asmjit/test/%.o: ../src/asmjit/test/%.cpp src/asmjit/test/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O1 -g3 -Wall -c -fmessage-length=0 -fpermissive -m64 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


