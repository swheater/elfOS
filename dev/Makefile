#
# Copyright (c) 2012-2013, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
#

export MAKE         = make
export CC           = arm-none-eabi-gcc
export CCFLAGS      = -Wall -mcpu=arm1176jzf-s -O -I$(CURDIR)/Headers
export AS           = arm-none-eabi-as
export ASFLAGS      = 
export LD           = arm-none-eabi-ld
export LDFLAGS      =
export OBJCOPY      = arm-none-eabi-objcopy
export OBJCOPYFLAGS =
export SIZE         = arm-none-eabi-size
export SIZEFLAGS    = 
export RM           = rm

OBJS = Source/Kernel/ARM/Boot.o \
       Source/Kernel/ARMv6/BootVirtualMemory.o Source/Kernel/ARMv6/BootHandlers.o \
       \
       Source/Kernel/ARM/Start.o Source/Kernel/Init.o \
       Source/Kernel/ARM/Thread.o \
       Source/Kernel/Handlers.o \
       Source/Kernel/ARMv6/CPUInfo.o Source/Kernel/Logging.o Source/Kernel/KDebug.o \
       Source/Kernel/ARM/HandlerVectors.o \
       \
       Source/StdLibrary/AEABI.o \
       Source/ELF/ELF32.o Source/ELF/ELF32_ARM_EABI.o \
       Source/String/String.o \
       Source/Device/BCM2835_miniUART.o Source/Device/BCM2835_GPIO.o \
       Source/Device/BCM2835_BSC.o Source/Device/BCM2835_SPI.o Source/Device/BCM2835_SystemTimer.o Source/Device/BCM2835_Timer.o \
       Source/Device/BCM2835_PWM.o Source/Device/BCM2835_EMMC.o \
       Source/Device/RaspPi_Status.o Source/Device/RaspPi_PiGlow.o Source/Device/RaspPi_PiLITEr.o Source/Device/RaspPi_BerryClip.o \
       Source/Device/RaspPi_Ladder.o Source/Device/RaspPi_DisplayTFT18.o \
       Source/Device/RaspPi_ILI9320.o Source/Device/RaspPi_SSD1351.o Source/Device/RaspPi_XPT2046.o \
       Source/Device/RaspPi_MotorPiTX.o Source/Device/RaspPi_elfOSDebug.o \
       Source/Device/RaspPi_ILSoftOLED.o Source/Device/SPI_SecureDigital.o Source/Device/SPI_MCP23S17.o 
#       Source/Kernel/Kernel/Process.o
#       Source/Kernel/ARM/Thread.o Source/Kernel/ARM/StartThreads.o \
#       Source/Kernel/ARMv6/MemoryManagement.o \

all: elfOS.img

$(OBJS):
	$(MAKE) -C Headers all
	$(MAKE) -C Source all

elfOS.elf elfOS.map: elfOS.lds $(OBJS)
	$(LD) $(LDFLAGS) -nostdlib -T elfOS.lds -o elfOS.elf -Map elfOS.map $(OBJS)
	$(SIZE) $(SIZEFLAGS) elfOS.elf

elfOS.img: elfOS.elf
	$(OBJCOPY) $(OBJCOPYFLAGS) -O binary elfOS.elf elfOS.img

clean:
	$(MAKE) -C Headers clean
	$(MAKE) -C Source clean
	$(RM) -f *~ *.elf *.img *.map
