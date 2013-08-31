#
# Copyright (c) 2012-2013, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
#

OBJS = BCM2835_miniUART.o BCM2835_GPIO.o BCM2835_BSC.o BCM2835_SPI.o BCM2835_Timer.o \
       RaspPi_DisplayTFT18.o RaspPi_PiGlow.o RaspPi_Status.o

all: $(OBJS)

.c.o:
	$(CC) $(CCFLAGS) -c $<

clean:
	$(RM) -f *~ *.o *.elf
