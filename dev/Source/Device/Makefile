#
# Copyright (c) 2012-2013, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
#

OBJS = RaspPi_UART.o RaspPi_GPIO.o RaspPi_I2C.o RaspPi_Timer.o 

all: $(OBJS)

.c.o:
	$(CC) $(CCFLAGS) -c $<

clean:
	$(RM) -f *~ *.o *.elf
