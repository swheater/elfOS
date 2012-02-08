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
	$(MAKE) -C boot all

all-kernel:
	$(MAKE) -C kernel all

elfOSBoot.img: elfOSBoot.elf
	$(OBJCOPY) -O binary elfOSBoot.elf elfOSBoot.img

elfOSBoot.elf: all-boot all-kernel
	$(LD) $(LDFLAGS) -T elfOSBoot.lds -o elfOSBoot.elf boot/arm/boot_zeropage.o kernel/init.o

clean:
	$(MAKE) -C boot clean
	$(MAKE) -C kernel clean
	$(RM) -f *~ *.elf *.img
