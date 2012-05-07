#
# Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
#

CC      = arm-none-eabi-gcc
CCFLAGS = -Wall -I../../Headers
RM      = rm

OBJS = String.o

all: $(OBJS)

.c.o:
	$(CC) $(CCFLAGS) -c $<

clean:
	$(RM) -f *~ *.o *.elf
