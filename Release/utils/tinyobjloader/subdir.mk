################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../utils/tinyobjloader/tiny_obj_loader.cc 

OBJS += \
./utils/tinyobjloader/tiny_obj_loader.o 

CC_DEPS += \
./utils/tinyobjloader/tiny_obj_loader.d 


# Each subdirectory must supply rules for building sources it contributes
utils/tinyobjloader/%.o: ../utils/tinyobjloader/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: NVCC Compiler'
	/usr/local/cuda-8.0/bin/nvcc -O3 -gencode arch=compute_35,code=sm_35 -gencode arch=compute_50,code=sm_50  -odir "utils/tinyobjloader" -M -o "$(@:%.o=%.d)" "$<"
	/usr/local/cuda-8.0/bin/nvcc -O3 --compile  -x c++ -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


