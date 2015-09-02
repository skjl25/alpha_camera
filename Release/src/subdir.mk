################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ClientSocket.cpp \
../src/Empty.cpp \
../src/ServerSocket.cpp 

CC_SRCS += \
../src/load_image.cc \
../src/viewer.cc 

OBJS += \
./src/ClientSocket.o \
./src/Empty.o \
./src/ServerSocket.o \
./src/load_image.o \
./src/viewer.o 

CC_DEPS += \
./src/load_image.d \
./src/viewer.d 

CPP_DEPS += \
./src/ClientSocket.d \
./src/Empty.d \
./src/ServerSocket.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


