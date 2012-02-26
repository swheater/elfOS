#
# Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
#

AS      = arm-elf-as
ASFLAGS = 
RM      = rm

all: ZeroPage.o

ZeroPage.o: ZeroPage.s
	$(AS) $(ASFLAGS) -o ZeroPage.o ZeroPage.s

clean:
	$(RM) -f *~ *.o
