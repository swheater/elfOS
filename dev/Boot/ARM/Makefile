#
# Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
#

AS      = arm-elf-as
ASFLAGS = 
RM      = rm

all: Boot_ZeroPage.o

Boot_ZeroPage.o: Boot_ZeroPage.s
	$(AS) $(ASFLAGS) -o Boot_ZeroPage.o Boot_ZeroPage.s

clean:
	$(RM) -f *~ *.o
