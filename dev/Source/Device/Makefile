#
# Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
#

CC      = arm-none-eabi-gcc
CCFLAGS = -Wall -O -I../../Headers
RM      = rm

OBJS = RaspPi_UART.o RaspPi_GPIO.o RaspPi_Timer.o 

all: $(OBJS)

.c.o:
	$(CC) $(CCFLAGS) -c $<

clean:
	$(RM) -f *~ *.o *.elf
