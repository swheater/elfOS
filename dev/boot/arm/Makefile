#
# Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
#

AS      = arm-elf-as
ASFLAGS = 
RM      = rm

all: boot_zeropage.o

boot_zeropage.o: boot_zeropage.s
	$(AS) $(ASFLAGS) -o boot_zeropage.o boot_zeropage.s

clean:
	$(RM) -f *~ *.o
