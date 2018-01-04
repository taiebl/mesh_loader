################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../rendering/renderer.cpp 

OBJS += \
./rendering/renderer.o 

CPP_DEPS += \
./rendering/renderer.d 


# Each subdirectory must supply rules for building sources it contributes
rendering/%.o: ../rendering/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: NVCC Compiler'
	/usr/local/cuda-8.0/bin/nvcc -O3 -gencode arch=compute_35,code=sm_35 -gencode arch=compute_50,code=sm_50  -odir "rendering" -M -o "$(@:%.o=%.d)" "$<"
	/usr/local/cuda-8.0/bin/nvcc -O3 --compile  -x c++ -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


