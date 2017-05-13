################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/AStar.cpp \
../src/InithPathfinding.cpp \
../src/Node.cpp \
../src/main.cpp 

OBJS += \
./src/AStar.o \
./src/InithPathfinding.o \
./src/Node.o \
./src/main.o 

CPP_DEPS += \
./src/AStar.d \
./src/InithPathfinding.d \
./src/Node.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


