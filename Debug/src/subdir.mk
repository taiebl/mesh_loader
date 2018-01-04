################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/main.cpp \
../src/plyReader.cpp 

OBJS += \
./src/main.o \
./src/plyReader.o 

CPP_DEPS += \
./src/main.d \
./src/plyReader.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: NVCC Compiler'
	/usr/local/cuda-8.0/bin/nvcc -I/home/taieb/NVIDIA_CUDA-8.0_Samples/common/inc -G -g -O0 --use_fast_math -std=c++11 -gencode arch=compute_35,code=sm_35  -odir "src" -M -o "$(@:%.o=%.d)" "$<"
	/usr/local/cuda-8.0/bin/nvcc -I/home/taieb/NVIDIA_CUDA-8.0_Samples/common/inc -G -g -O0 --use_fast_math -std=c++11 --compile  -x c++ -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


