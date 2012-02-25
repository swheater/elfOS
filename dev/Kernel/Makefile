#
# Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
#

CC      = arm-elf-gcc
CCFLAGS = 
RM      = rm

KERNEL_OBJS = Kernel_Init.o

all: Kernel_Init.o ELF32.o

.c.o:
	$(CC) $(CCFLAGS) -c $<

ELF32.o: ELF32.c
	$(CC) $(CCFLAGS) -c ELF32.c

clean:
	$(RM) -f *~ *.o
