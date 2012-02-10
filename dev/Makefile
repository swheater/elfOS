#
# Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
#

LD      = arm-gp2x-linux-ld
LDFLAGS = 
OBJCOPY = arm-gp2x-linux-objcopy
MAKE    = make
RM      = rm

all: all-boot all-elf elfOSBoot.img

all-boot:
	$(MAKE) -C boot all

all-elf:
	$(MAKE) -C elf all

elfOSBoot.img: elfOSBoot.elf
	$(OBJCOPY) -O binary elfOSBoot.elf elfOSBoot.img

elfOSBoot.elf:
	$(LD) $(LDFLAGS) -T elfOSBoot.lds -o elfOSBoot.elf boot/arm/BootZeroPage.o boot/BaseELFLoader.o

clean:
	$(MAKE) -C boot clean
	$(MAKE) -C elf clean
	$(RM) -f *~ *.elf *.img
