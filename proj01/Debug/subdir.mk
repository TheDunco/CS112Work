################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../PlayList.cpp \
../PlayListTester.cpp \
../Song.cpp \
../SongTester.cpp \
../TUI.cpp \
../main.cpp 

OBJS += \
./PlayList.o \
./PlayListTester.o \
./Song.o \
./SongTester.o \
./TUI.o \
./main.o 

CPP_DEPS += \
./PlayList.d \
./PlayListTester.d \
./Song.d \
./SongTester.d \
./TUI.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


