#
# Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
#

CC     = arm-gp2x-linux-gcc
CFLAGS = -Wall -O2
MAKE   = make
RM     = rm

all: ELF.o

ELF.o: ELF.c ELF.h
	$(CC) $(CCFLAGS) -c ELF.c

clean:
	$(RM) -f *~ *.o
