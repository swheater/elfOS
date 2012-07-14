#
# Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
#

AS      = arm-none-eabi-as
ASFLAGS = 
CC      = arm-none-eabi-gcc
CCFLAGS = -Wall -O -I../../../Headers
RM      = rm

OBJS = Thread.o StartThreads.o

all: $(OBJS)

.s.o:
	$(AS) $(ASFLAGS) -o $@ $<

.c.o:
	$(CC) $(CCFLAGS) -c $<

clean:
	$(RM) -f *~ *.o
