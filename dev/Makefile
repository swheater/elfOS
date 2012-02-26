#
# Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
#

LD      = arm-elf-ld
LDFLAGS = 
OBJCOPY = arm-elf-objcopy
SIZE    = arm-elf-size
MAKE    = make
RM      = rm

all: elfOSBoot.img
	$(SIZE) elfOSBoot.elf

all-boot:
	$(MAKE) -C Boot all

all-kernel:
	$(MAKE) -C Kernel all

elfOSBoot.img: elfOSBoot.elf
	$(OBJCOPY) -O binary elfOSBoot.elf elfOSBoot.img

elfOSBoot.elf elfOSBoot.map: all-boot all-kernel
	$(LD) $(LDFLAGS) -T elfOSBoot.lds -o elfOSBoot.elf -Map elfOSBoot.map Boot/ARM/Boot_ZeroPage.o Kernel/Kernel_Init.o

clean:
	$(MAKE) -C Boot clean
	$(MAKE) -C Kernel clean
	$(RM) -f *~ *.elf *.img *.map
