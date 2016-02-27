################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Jerry.c \
../src/http_core.c \
../src/http_parser.c \
../src/pool.c 

OBJS += \
./src/Jerry.o \
./src/http_core.o \
./src/http_parser.o \
./src/pool.o 

C_DEPS += \
./src/Jerry.d \
./src/http_core.d \
./src/http_parser.d \
./src/pool.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


