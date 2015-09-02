################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/root/workspace/include-files/TCPClientSocket.cpp \
/root/workspace/include-files/TCPServerSocket.cpp \
/root/workspace/include-files/camera.cpp \
/root/workspace/include-files/cvideo.cpp \
/root/workspace/include-files/image_processing.cpp \
/root/workspace/include-files/m3dvc.cpp \
/root/workspace/include-files/utility.cpp \
/root/workspace/include-files/wlessTools.cpp 

C_SRCS += \
/root/workspace/include-files/iwlib.c 

CC_SRCS += \
/root/workspace/include-files/load_image.cc \
/root/workspace/include-files/viewer.cc 

OBJS += \
./src/include/TCPClientSocket.o \
./src/include/TCPServerSocket.o \
./src/include/camera.o \
./src/include/cvideo.o \
./src/include/image_processing.o \
./src/include/iwlib.o \
./src/include/load_image.o \
./src/include/m3dvc.o \
./src/include/utility.o \
./src/include/viewer.o \
./src/include/wlessTools.o 

C_DEPS += \
./src/include/iwlib.d 

CC_DEPS += \
./src/include/load_image.d \
./src/include/viewer.d 

CPP_DEPS += \
./src/include/TCPClientSocket.d \
./src/include/TCPServerSocket.d \
./src/include/camera.d \
./src/include/cvideo.d \
./src/include/image_processing.d \
./src/include/m3dvc.d \
./src/include/utility.d \
./src/include/wlessTools.d 


# Each subdirectory must supply rules for building sources it contributes
src/include/TCPClientSocket.o: /root/workspace/include-files/TCPClientSocket.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/include/GL -I/usr/include -I/usr/local/include/libfreenect -I/usr/include/opencv -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/include/TCPServerSocket.o: /root/workspace/include-files/TCPServerSocket.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/include/GL -I/usr/include -I/usr/local/include/libfreenect -I/usr/include/opencv -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/include/camera.o: /root/workspace/include-files/camera.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/include/GL -I/usr/include -I/usr/local/include/libfreenect -I/usr/include/opencv -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/include/cvideo.o: /root/workspace/include-files/cvideo.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/include/GL -I/usr/include -I/usr/local/include/libfreenect -I/usr/include/opencv -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/include/image_processing.o: /root/workspace/include-files/image_processing.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/include/GL -I/usr/include -I/usr/local/include/libfreenect -I/usr/include/opencv -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/include/iwlib.o: /root/workspace/include-files/iwlib.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/include/load_image.o: /root/workspace/include-files/load_image.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/include/GL -I/usr/include -I/usr/local/include/libfreenect -I/usr/include/opencv -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/include/m3dvc.o: /root/workspace/include-files/m3dvc.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/include/GL -I/usr/include -I/usr/local/include/libfreenect -I/usr/include/opencv -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/include/utility.o: /root/workspace/include-files/utility.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/include/GL -I/usr/include -I/usr/local/include/libfreenect -I/usr/include/opencv -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/include/viewer.o: /root/workspace/include-files/viewer.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/include/GL -I/usr/include -I/usr/local/include/libfreenect -I/usr/include/opencv -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/include/wlessTools.o: /root/workspace/include-files/wlessTools.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/include/GL -I/usr/include -I/usr/local/include/libfreenect -I/usr/include/opencv -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


