################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Dave/Generated/SPI_SLAVE/spi_slave.c \
../Dave/Generated/SPI_SLAVE/spi_slave_conf.c 

OBJS += \
./Dave/Generated/SPI_SLAVE/spi_slave.o \
./Dave/Generated/SPI_SLAVE/spi_slave_conf.o 

C_DEPS += \
./Dave/Generated/SPI_SLAVE/spi_slave.d \
./Dave/Generated/SPI_SLAVE/spi_slave_conf.d 


# Each subdirectory must supply rules for building sources it contributes
Dave/Generated/SPI_SLAVE/%.o: ../Dave/Generated/SPI_SLAVE/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM-GCC C Compiler'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-gcc" -MMD -MT "$@" -DXMC1402_T038x0200 -I"$(PROJECT_LOC)/Libraries/XMCLib/inc" -I"$(PROJECT_LOC)/Libraries/CMSIS/Include" -I"$(PROJECT_LOC)/Libraries/CMSIS/Infineon/XMC1400_series/Include" -I"$(PROJECT_LOC)" -I"$(PROJECT_LOC)/Dave/Generated" -I"$(PROJECT_LOC)/Libraries" -Os -ffunction-sections -fdata-sections -Wall -std=gnu99 -Wa,-adhlns="$@.lst" -pipe -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d) $@" -mcpu=cortex-m0 -mthumb -o "$@" "$<" 
	@echo 'Finished building: $<'
	@echo.

