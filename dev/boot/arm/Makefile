#
# Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
#

AS      = arm-gp2x-linux-as
ASFLAGS = 
RM      = rm

all:BootZeroPage.o

BootZeroPage.o: BootZeroPage.s
	$(AS) $(ASFLAGS) -o BootZeroPage.o BootZeroPage.s

clean:
	$(RM) -f *~ *.o
