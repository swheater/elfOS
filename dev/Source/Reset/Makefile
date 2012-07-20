#
# Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
#

CC      = arm-none-eabi-gcc
CCFLAGS = -Wall -O -I../../Headers
MAKE    = make
RM      = rm

OBJS = UART.o

all: $(OBJS)
	$(MAKE) -C ARM all
	$(MAKE) -C ARMv6 all

.c.o:
	$(CC) $(CCFLAGS) -c $<

clean:
	$(MAKE) -C ARM clean
	$(MAKE) -C ARMv6 clean
	$(RM) -f *~ *.o
