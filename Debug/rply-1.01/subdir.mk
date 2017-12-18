################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../rply-1.01/rply.c 

OBJS += \
./rply-1.01/rply.o 

C_DEPS += \
./rply-1.01/rply.d 


# Each subdirectory must supply rules for building sources it contributes
rply-1.01/%.o: ../rply-1.01/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: NVCC Compiler'
	/usr/local/cuda-8.0/bin/nvcc -G -g -O0 -std=c++11 -gencode arch=compute_35,code=sm_35 -gencode arch=compute_50,code=sm_50  -odir "rply-1.01" -M -o "$(@:%.o=%.d)" "$<"
	/usr/local/cuda-8.0/bin/nvcc -G -g -O0 -std=c++11 --compile  -x c -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


