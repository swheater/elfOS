#
# Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
#

CC     = arm-gp2x-linux-gcc
CFLAGS = -Wall -O2
MAKE   = make
RM     = rm

all: ELF32.o

ELF32.o: ELF32.c ELF32.h
	$(CC) $(CCFLAGS) -c ELF32.c

clean:
	$(RM) -f *~ *.o
