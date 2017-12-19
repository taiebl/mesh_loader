################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../utils/Mesh.cpp \
../utils/OptiXMesh.cpp \
../utils/sutil.cpp 

OBJS += \
./utils/Mesh.o \
./utils/OptiXMesh.o \
./utils/sutil.o 

CPP_DEPS += \
./utils/Mesh.d \
./utils/OptiXMesh.d \
./utils/sutil.d 


# Each subdirectory must supply rules for building sources it contributes
utils/%.o: ../utils/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: NVCC Compiler'
	/usr/local/cuda-8.0/bin/nvcc -G -g -O0 -std=c++11 -gencode arch=compute_35,code=sm_35 -gencode arch=compute_50,code=sm_50  -odir "utils" -M -o "$(@:%.o=%.d)" "$<"
	/usr/local/cuda-8.0/bin/nvcc -G -g -O0 -std=c++11 --compile  -x c++ -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


