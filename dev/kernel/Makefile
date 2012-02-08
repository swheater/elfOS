#
# Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
#

CC      = arm-elf-gcc
CCFLAGS = 
RM      = rm

all: init.o

init.o: init.c
	$(CC) $(CCFLAGS) -c init.c

clean:
	$(RM) -f *~ *.o
