################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../gl/gl.cpp 

OBJS += \
./gl/gl.o 

CPP_DEPS += \
./gl/gl.d 


# Each subdirectory must supply rules for building sources it contributes
gl/%.o: ../gl/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: NVCC Compiler'
	/usr/local/cuda-8.0/bin/nvcc -G -g -O0 -std=c++11 -gencode arch=compute_35,code=sm_35 -gencode arch=compute_50,code=sm_50  -odir "gl" -M -o "$(@:%.o=%.d)" "$<"
	/usr/local/cuda-8.0/bin/nvcc -G -g -O0 -std=c++11 --compile  -x c++ -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


