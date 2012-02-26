#
# Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
#

CC      = arm-elf-gcc
CCFLAGS = -fno-hosted -fno-builtin
RM      = rm

OBJS = String.o

all: $(OBJS)

.c.o:
	$(CC) $(CCFLAGS) -I../../Headers -fPIC -c $<

clean:
	$(RM) -f *~ *.o *.elf
