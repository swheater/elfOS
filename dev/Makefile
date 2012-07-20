#
# Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
#

LD      = arm-none-eabi-ld
LDFLAGS = 
OBJCOPY = arm-none-eabi-objcopy
SIZE    = arm-none-eabi-size
MAKE    = make
RM      = rm

OBJS = Source/Reset/ARM/ZeroPage.o Source/Reset/ARMv6/Init.o Source/Reset/UART.o \
       \
       Source/Kernel/ARM/Start.o Source/Kernel/Init.o \
       Source/Kernel/Handlers.o \
       Source/Kernel/ARM/Thread.o Source/Kernel/ARM/StartThreads.o \
       Source/Kernel/ARMv6/MemoryManagement.o \
       Source/Kernel/ARMv6/CPUInfo.o Source/Kernel/Logging.o Source/Kernel/KDebug.o \
       \
       Source/StdLibrary/AEABI.o \
       Source/ELF/ELF32.o Source/ELF/ELF32_ARM_EABI.o \
       Source/String/String.o \
       Source/elfOS/Container.o Source/elfOS/Thread.o \
       Source/Device/RaspPi_UART.o Source/Device/RaspPi_GPIO.o Source/Device/RaspPi_Timer.o

all: elfOS.img

$(OBJS):
	$(MAKE) -C Headers all
	$(MAKE) -C Source all

elfOS.elf elfOS.map: elfOS.lds $(OBJS)
	$(LD) $(LDFLAGS) -nostdlib -T elfOS.lds -o elfOS.elf -Map elfOS.map $(OBJS)
	$(SIZE) elfOS.elf

elfOS.img: elfOS.elf
	$(OBJCOPY) -O binary elfOS.elf elfOS.img

clean:
	$(MAKE) -C Headers clean
	$(MAKE) -C Source clean
	$(RM) -f *~ *.elf *.img *.map
