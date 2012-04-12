#
# Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
#

LD      = arm-none-eabi-ld
LDFLAGS = 
OBJCOPY = arm-none-eabi-objcopy
SIZE    = arm-none-eabi-size
MAKE    = make
RM      = rm

OBJS = Source/Boot/ARM/ZeroPage.o Source/Kernel/Init.o Source/ELF/ELF32.o Source/String/String.o

all: elfOSBoot.img
	$(SIZE) elfOSBoot.elf

elfOSBoot.elf elfOSBoot.map:
	$(MAKE) -C Headers all
	$(MAKE) -C Source all
	$(LD) $(LDFLAGS) -nostdlib -T elfOSBoot.lds -o elfOSBoot.elf -Map elfOSBoot.map $(OBJS)

elfOSBoot.img: elfOSBoot.elf
	$(OBJCOPY) -O binary elfOSBoot.elf elfOSBoot.img

clean:
	$(MAKE) -C Headers clean
	$(MAKE) -C Source clean
	$(RM) -f *~ *.elf *.img *.map
